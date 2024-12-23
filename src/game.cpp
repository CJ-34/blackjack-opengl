#include "game.h"
#include "graphics/resourceManager.h"

#include "imgui.h" 
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"



bool showHelpWindow = false;
ImGuiWindowFlags window_flags =  ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;

Game::Game(GLFWwindow *window)
    : state(GAME_MENU), window(window), table(Player("Player")), firstGame(true) 
{
}

Game::~Game()
{
    delete Renderer;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    UnloadSound(dealcardSound);

    CloseAudioDevice();
}

void Game::init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

     // Load fonts
    ImFontConfig config;
    config.MergeMode = false;  // Don't use MergeMode for the first font

    // Define a broad range of Unicode characters
    static const ImWchar ranges[] = {
        0x0020, 0x00FF,  // Basic Latin + Latin Supplement
        0x0100, 0x017F,  // Latin Extended-A
        0  // End of ranges
    };

    io.Fonts->AddFontFromFileTTF("resources/fonts/Roboto-Regular.ttf", 18.0f, &config, ranges);

    // Build the font atlas
    io.Fonts->Build();

    Shader shader = ResourceManager::LoadShader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag", "cardShader");

    glm::mat4 projection = glm::ortho(0.0f, (float)800, (float)600, 0.0f, -1.0f, 1.0f);
    shader.Use();
    shader.SetInt("card", 0);
    shader.SetMat4("projection", projection);

    Renderer = new CardRenderer(ResourceManager::GetShader("cardShader"));

    for (int suit = (int) Suit::HEARTS; suit <= (int) Suit::SPADES; suit++) {
        for (int rank = (int) Rank::ACE; rank <= (int) Rank::KING; rank++) {
            Card card {(Suit) suit, (Rank) rank};
            ResourceManager::LoadTexture(card.getImagePath().c_str(), card.getPhotoName(), true);
        } 
    }

    InitAudioDevice();

    if (!IsAudioDeviceReady()) {
        std::cerr << "Failed to initialize audio device" << std::endl;
    } else {
        std::cout << "Audio device initialized" << std::endl;
    }
    
    dealcardSound = LoadSound("resources/SFX/dealcard.wav");

    ResourceManager::LoadTexture("resources/cards/background.jpg", "background", false);
    ResourceManager::LoadTexture("resources/screen/blackjackTitle.png", "title", true);
    ResourceManager::LoadTexture("resources/screen/author.png", "author", true);
    ResourceManager::LoadTexture("resources/cards/BACK.png", "card_back", false);
    ResourceManager::LoadTexture("resources/screen/youLose.png", "you_lose", true);
    ResourceManager::LoadTexture("resources/screen/youWin.png", "you_win", true);
}

void Game::renderHand(const Hand& hand, const glm::vec2 startPos)
{
    for (size_t i = 0; i < hand.getCards().size(); i++) {
        Texture cardTexture = ResourceManager::GetTexture(hand.getCards()[i].getPhotoName());
        Renderer->Draw(cardTexture, startPos + glm::vec2(i * (300 * 0.3f + 0.5f), 0), 0.0f); 
    }
}

void Game::renderDealerHand(const glm::vec2 startPos)
{
    Hand hand = table.getDealer().getHand();
    if (hand.getCards().empty()) return;

    Texture firstCardTexture = ResourceManager::GetTexture(hand.getCards()[0].getPhotoName());
    Renderer->Draw(firstCardTexture, startPos, 0.0f);

    Texture cardBackTexture = ResourceManager::GetTexture("card_back");
    for (size_t i = 1; i < hand.getCards().size(); i++) {
        Renderer->Draw(cardBackTexture, startPos + glm::vec2(i * (300 * 0.3f + 0.5f), 0), 0.0f);
    }
    
}

void Game::handlePlayerTurn() {
    if (ImGui::Button("Dodeli karto")) {
        table.playerTurn();

        if (IsSoundPlaying(dealcardSound)) StopSound(dealcardSound);

        PlaySound(dealcardSound);

        if (table.getPlayer().isBusted()) {
            this->state = GameState::GAME_OVER;
        }
    }

    ImGui::SameLine(0, 10);

    if (ImGui::Button("Ustavi")) {
        handleDealerTurn();
        this->state = GameState::GAME_OVER;
    }
}

void Game::handleDealerTurn() {
   table.dealerTurn(); 
}

void Game::update()
{
    if (this->state == GAME_RUNNING) {
        if (table.getPlayer().isBlackjack() || table.getDealer().isBlackjack()) {
            std::cout << "Blackjack detected, transitioning to GAME_OVER" << std::endl;
            this->state = GameState::GAME_OVER;
        }
    }
}

void Game::render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Texture backgroundTexture = ResourceManager::GetTexture("background");
    Renderer->Draw(backgroundTexture, glm::vec2(0, 0), 0.0f, glm::vec2(800, 600), false);


    if (this->state == GAME_MENU) {

        Texture titleTexture = ResourceManager::GetTexture("title");
        Renderer->Draw(titleTexture, glm::vec2(150, 25), 0.0f, glm::vec2(500, 300), false);
        
        Texture authorTexture = ResourceManager::GetTexture("author");
        Renderer->Draw(authorTexture, glm::vec2(150, 350), 0.0f, glm::vec2(500, 300), false);

        if (firstGame && !showHelpWindow) {
            ImVec2 windowSize(400, 140);  // Set window size (you can adjust as needed)
            ImVec2 windowPos((ImGui::GetIO().DisplaySize.x - windowSize.x) * 0.5f, 
                             (ImGui::GetIO().DisplaySize.y - windowSize.y) * 0.5f); // Center the window

            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f); // Set window corner to round
            ImGui::Begin("Dobrodošli", nullptr, window_flags);


            ImGui::SetWindowPos(windowPos);   // Set the position of the window
            ImGui::SetWindowSize(windowSize);

            ImGui::Text("Uživajte v tej (nekoliko) točni simulaciji blackjacka");

            if (ImGui::Button("Začni novo igro")) {
                table.startGame();
                firstGame = false;
                this->state = GameState::GAME_RUNNING;
            }

            ImGui::SameLine(0, 10);

            if (ImGui::Button("Navodila in pravila")) {
                showHelpWindow = true;
            }

            ImGui::Text("Avtor: Miguel Angel Sala");

            if (ImGui::Button("Izhod")) {
                glfwSetWindowShouldClose(window, true);
            }

            ImGui::End();
            ImGui::PopStyleVar();
        } else if (!firstGame) {
            table.startGame();
            this->state = GameState::GAME_RUNNING;
        }
    } else if (this->state == GAME_RUNNING) {
        ImVec2 windowPos = ImVec2(570, 210);
        ImVec2 windowSize = ImVec2(200, 200);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
        ImGui::Begin("Blackjack", nullptr, window_flags);

        ImGui::SetWindowPos(windowPos);
        ImGui::SetWindowSize(windowSize);

        renderDealerHand(glm::vec2(100, 100));

        ImGui::Text("Player: %d", table.getPlayer().getHand().getHandValue());
        renderHand(table.getPlayer().getHand(), glm::vec2(100, 400));

        handlePlayerTurn();

        ImGui::End();
        ImGui::PopStyleVar();
    } else if (this->state == GAME_OVER) {
        GameResult decision = table.determineWinner();

        ImVec2 windowPos = ImVec2(570, 210);
        ImVec2 windowSize = ImVec2(200, 200);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
        ImGui::Begin("Konec igre", nullptr, window_flags);

        ImGui::SetWindowPos(windowPos);
        ImGui::SetWindowSize(windowSize);
        
        renderHand(table.getDealer().getHand(), glm::vec2(100, 100));
        renderHand(table.getPlayer().getHand(), glm::vec2(100, 400));

        int playerValue = table.getPlayer().getHand().getHandValue();
        int dealerValue = table.getDealer().getHand().getHandValue();

        ImGui::Text("Igralec: %d", playerValue);
        ImGui::Text("Delivec: %d", dealerValue);


        ImGui::TextWrapped("%s", decision.result.c_str());

        if (decision.playerWin) {
			Texture youWinTexture = ResourceManager::GetTexture("you_win");
			Renderer->Draw(youWinTexture, glm::vec2(150, 100), 0.0f, glm::vec2(500, 300), false);
        }
        else {
			Texture youLoseTexture = ResourceManager::GetTexture("you_lose");
			Renderer->Draw(youLoseTexture, glm::vec2(150, 100), 0.0f, glm::vec2(500, 300), false);
        }


        if (ImGui::Button("Znova")) {
            table.resetTable();
            this->state = GAME_MENU;
        }

        ImGui::SameLine(0, 10);

        if (ImGui::Button("Nazaj na meni")) {
            table.resetTable();
            firstGame = true;
            this->state = GAME_MENU;
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }

    if (showHelpWindow) {
        ImVec2 windowSize(600, 300);
        ImVec2 windowPos((ImGui::GetIO().DisplaySize.x - windowSize.x) * 0.5f, 
                         (ImGui::GetIO().DisplaySize.y - windowSize.y) * 0.5f);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
        ImGui::Begin("Navodila in pravila", &showHelpWindow, window_flags);

        ImGui::SetWindowPos(windowPos);
        ImGui::SetWindowSize(windowSize);

        ImGui::Text("Kako igrati blackjack:");
        ImGui::Text("- Cilj igre je zbrati čim večjo vsoto točk, ne da bi presegli 21.");
        ImGui::Text("- As šteje 1 ali 11 točk, karte od 2 do 10 pa toliko točk, kot je napisano na njih.");
        ImGui::Text("- Igralec lahko zahteva dodatno karto (Dodeli karto) ali pa se odloči, da ne bo več vzel kart (Ustavi).");
        ImGui::Text("- Če igralec preneha z jemanjem kart, je na vrsti delivec.");
        ImGui::Text("- Delivec (računalnik) mora vzeti karto, če je njegova vsota točk manjša od 17.");
        ImGui::Text("- Delivec ne more prenehati z jemanjem kart");
        ImGui::Text("- Če igralec preseže 21 točk, izgubi igro.");
        ImGui::Text("- Če igralec in delivec presežeta 21 točk, je igra neodločena.");
        ImGui::Text("- Če igralec igralec ima več točk kot delivec, zmaga igralec.");

        if (ImGui::Button("Zapri")) {
            showHelpWindow = false;
        }

        ImGui::End();
        ImGui::PopStyleVar();
    }

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

