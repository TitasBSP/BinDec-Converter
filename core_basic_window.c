#include "raylib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main()
{
    // VARIABLES FOR TITLE SCREEN
    //--------------------------------------------------------------------------------------

    // Defining screen size - exactly half of 1080p here!
    int screenWidth = 960;
    int screenHeight = 540;
    
    // Splash screen text
    float titleX = 120;
    float titleY = 230;
    int titleSize = 50;
    
    // Binary button settings
    float ButtonBinaryX = 300;
    float ButtonBinaryY = 220;
    Rectangle ButtonBinary = {ButtonBinaryX, ButtonBinaryY, 300, 75};

    float alphaButtonBinary = 0.0f; // This is used for the FADE!
    
    // Binary text
    float TextBinaryX = 350;
    float TextBinaryY = 235;
    
    // Decimal button settings
    float ButtonDecimalX = 300;
    float ButtonDecimalY = 350;
    Rectangle ButtonDecimal = {ButtonDecimalX, ButtonDecimalY, 300, 75};
    
    float alphaButtonDecimal = 0.0f;
    
    // Decimal text
    float TextDecimalX = 340;
    float TextDecimalY = 365;
    
    // ----------------- BINARY - SCREEN ---------------------------- //
    
    // Input window
    float windowBinaryX = 220;
    float windowBinaryY = 250;
    Rectangle windowBinary = {windowBinaryX, windowBinaryY, 500, 75};
    
    // Convert button
    float convertBinaryX = 360;
    float convertBinaryY = 360;
    Rectangle convertBinary = {convertBinaryX, convertBinaryY, 200, 50};
    
    float alphaConvertBinary = 0.0f;
    
    // Binary output window
    float outputBinaryX = 360;
    float outputBinaryY = 240;
    Rectangle outputBinary = {outputBinaryX, outputBinaryY, 200, 75};
    
    float alphaOutputBinary = 0.0f;
    
    // ------------------- DECIMAL - SCREEN -------------------------- //

    // Identical for decimal
    float windowDecimalX = 310;
    float windowDecimalY = 250;
    Rectangle windowDecimal = {windowDecimalX, windowDecimalY, 300, 75};
    
    float convertDecimalX = 360;
    float convertDecimalY = 360;
    Rectangle convertDecimal = {convertDecimalX, convertDecimalY, 200, 50};
    
    float alphaConvertDecimal = 0.0f;
    
    float outputDecimalX = 220;
    float outputDecimalY = 250;
    Rectangle outputDecimal = {outputDecimalX, outputDecimalY, 500, 75};
    
    float alphaOutputDecimal = 0.0f;
    
    // --------------------- LANGUAGE-BAR ------------------------- //
    
    // Language text square
    float langBarX = 770;
    float langBarY = 480;
    Rectangle langBar = {langBarX, langBarY, 200, 100};
    
    // Language text
    float langTextX = 790;
    float langTextY = 500;
    float langTextS = 25;
    
    float alphaLangBar = 0.0f;
    
    // Pop-Up Window
    float langPopUpX = 770;
    float langPopUpY = 380;
    Rectangle langPopUp = {langPopUpX, langPopUpY, 200, 200};
    
    float alphaLangPop = 0.0f;
    
    // Invis button for norwegian
    float btnNorskX = 780;
    float btnNorskY = 380;
    Rectangle btnNorsk = {btnNorskX, btnNorskY, 150, 40};
    
    // Invis button for english
    float btnEnglishX = 780;
    float btnEnglishY = 430;
    Rectangle btnEnglish = {btnEnglishX, btnEnglishY, 150, 40};
    
    float invisBtnNorsk = 0.0f;
    float invisBtnEnglish = 0.0f;
    
    // --------------------- MISCELLANEOUS ------------------------ //
    
    InitWindow(screenWidth, screenHeight, "Binary & Decimal Converter");

    SetTargetFPS(60);
    
    // Transitions & Such
    bool clearScreen = false;
    bool langPop = false;
    
    bool displayBinary = false;
    bool displayDecimal = false;
    
    bool displayBinaryResult = false;
    bool displayDecimalResult = false;
    
    char outputTextBinary[4];
    char outputTextDecimal[9];
    
    bool errorDecimal = false;
    
    //----------------------------- MULTI-LANGUAGE SUPPORT -----------------------------------//
    
    bool englishLang = true;
    bool norwegianLang = false;
    
    // Defining all existing text in application
    
    char TextBinary[8] = "BINARY";
    char TextDecimal[8] = "DECIMAL";
    
    char Copyright[64] = "© 2025 - Elevens";
    
    char title[64] = "Binary & Decimal Converter";
    
    char binaryAsk[128] = "Please enter a BINARY number to convert\n               (00000000 - 11111111)";
    char binaryConvert[16] = "CONVERT";
    char binaryAskResult[128] = "The binary equivalent to [              ] is";
    char returnBinary[32] = "PRESS [SPACE] TO RETURN";
    
    char decimalAsk[128] = "Please enter a DECIMAL number to convert\n                       (1-255)";
    char decimalConvert[16] = "CONVERT";
    char decimalValueException[32] = "VALUE MUST BE BETWEEN [1-255]!";
    char decimalAskRes[128] = "The decimal equivalent to [      ] is";
    char returnDecimal[32] = "PRESS [SPACE] TO RETURN";
    
    char langText[16] = "LANGUAGES";

    //-------------------------------- Handling user input --------------------------------//
    
    // Stores the binary and decimals!
    char binaryInput[9] = "";
    char decimalInput[4] = "";
    int binaryLen = 0;
    int decimalLen = 0;
    
    // Outputs for the converted stored numbers
    int binaryArray[8] = {0};
    char resultDecimal[8] = "";
    
    //-------------------------------------------------------------------------------------//
    

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {  
        Vector2 mousePos = GetMousePosition(); // This grabs the mouse's position 60 times per second
            
        // Handling color change and confirming clicks on buttons
        bool isHoveringBinary = CheckCollisionPointRec(mousePos, ButtonBinary);
        bool isHoveringDecimal = CheckCollisionPointRec(mousePos, ButtonDecimal);
        
        bool isHoveringLangBar = CheckCollisionPointRec(mousePos, langBar);
        bool isHoveringLangPopUp = CheckCollisionPointRec(mousePos, langPopUp);
        
        bool isHoveringBtnNorsk = CheckCollisionPointRec(mousePos, btnNorsk);
        bool isHoveringBtnEnglish = CheckCollisionPointRec(mousePos, btnEnglish);
        
        bool isHoveringConvertBinary = CheckCollisionPointRec(mousePos, convertBinary);
        bool isHoveringConvertDecimal = CheckCollisionPointRec(mousePos, convertDecimal);
        
///////////////////////////////////// BINARY ////////////////////////////////////////////////

        if (displayBinary) { // If the binary screen is on
            int pressedKey = GetCharPressed(); // The entered keys will go into this variable
            while (pressedKey > 0) { // And long as there are more than 0 characters
            
                if (binaryLen < 8 && (pressedKey == '0' || pressedKey == '1')) { // The statement will check that the binary array does not exceed more than 8 characters, and that only the keys 0 and 1 are typed
                    binaryInput[binaryLen] = (char)pressedKey; // Every key will be allocated a spot in the binaryInput ARRAY!
                    binaryLen++; // BinaryLen's count will go up signalizing that a spot has been taken up!
                    binaryInput[binaryLen] = '\0'; // If the amount of characters exceeds the limit, then this line of code will do an invisible backspace which prevents overflow!
                    
                }
                pressedKey = GetCharPressed(); // Ensures that you can keep entering keys during the loop's lifespan.
            }
            
            // The logic from line 156 is reused for the BACKSPACE key which serves the same purpose, but here we can delete keys at will.
            if (IsKeyPressed(KEY_BACKSPACE) && binaryLen > 0) { 
                binaryLen--;
                binaryInput[binaryLen] = '\0';
            }
            
            // Binary calculation ensures that there is at least one character inserted, and either you have pressed the ENTER key or clicked on the BINARY button!
            if (IsKeyPressed(KEY_ENTER) && binaryLen > 0 || isHoveringConvertBinary && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && binaryLen > 0) {
                int decimalNumbers = 128; // We use this to go down the binary pipeline, starting from 2^7 and downwards
                int outputDecimal = 0; // This is used to sum up the total
                
                // This loop handles going down from 2^7 to 2^6 and so on. 
                for (int binaryCounter = 0; binaryCounter < binaryLen; ++binaryCounter) { // We start with 0 on the counter and go up until it hits the binaryLen which could be anywhere between 1-8 depending on the user's input and then increase the counter with each loop iteration
                    if (binaryInput[binaryCounter] == '1') { 
                        outputDecimal += decimalNumbers; // If the resulting number is a 1, then it will be added from the decimalNumbers variable which goes down the list!
                    }
                    decimalNumbers /= 2; // Otherwise it will keep dividing that number by 2 until it finds something else
                };
                displayBinaryResult = true; // After that, the block for showing the output will be displayed
                
                // DEBUG IN CONSOLE
                sprintf(outputTextBinary, "%d", outputDecimal);
                printf("%s", outputTextBinary);
                fflush(stdout);
                
            }
        }
        
///////////////////////////////// DECIMAL ////////////////////////////////

        // Most of the logic for this portion has been recycled except for calculations!
        if (displayDecimal) {
            int pressedKey = GetCharPressed();
            while (pressedKey > 0) {
            
                if (decimalLen < 3 && pressedKey >= '0' && pressedKey <= '9') {
                    decimalInput[decimalLen] = (char)pressedKey;
                    decimalLen++;
                    decimalInput[decimalLen] = '\0';
                    
                }
                pressedKey = GetCharPressed();
            }
            
            if (IsKeyPressed(KEY_BACKSPACE) && decimalLen > 0) {
                decimalLen--;
                decimalInput[decimalLen] = '\0';
            }
            
            int decimalValue = atoi(decimalInput);  // Converts the string to an integer
            
            if ((IsKeyPressed(KEY_ENTER) && decimalLen < 4 && decimalLen > 0 && decimalValue <= 255 && decimalValue > 0) ||
                (isHoveringConvertDecimal && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && decimalLen < 4 && decimalLen > 0 && decimalValue <= 255)) {           
                
                int binaryNumbers = 128;
                memset(resultDecimal, 0, sizeof(resultDecimal)); // Ensures that resultDecimal is reset properly before use
                
                for (int binaryCounter = 0; binaryCounter < 8; ++binaryCounter) { // binaryCounter goes through all 8 digits of the binary table!
                    binaryArray[binaryCounter] = (decimalValue / binaryNumbers) ? 1 : 0;
                    if (binaryArray[binaryCounter]) {
                        decimalValue -= binaryNumbers; // The current number is subtracted with the binary sequence number and the loop is repeated until binaryCounter goes up to 8
                        }
                        binaryNumbers /= 2; // If the inputNumber is indivisible by the current one, it will be divided by two
                }
                
                for (int i = 0; i < 8; i++) {
                    resultDecimal[i] = binaryArray[i] + '0'; // "Converts" int to char ('0' or '1')
                }
                resultDecimal[8] = '\0';
                
                displayDecimalResult = true; // Displays the decimal output screen
                
                // DEBUG
                sprintf(outputTextDecimal, "%s", resultDecimal);
                printf("Result: %s", outputTextDecimal);
                fflush(stdout); // Debug to see working number
                
            } else if ((IsKeyPressed(KEY_ENTER) && decimalValue > 255) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && decimalValue > 255)) { // If the number that was typed in is higher than 255 the errorDecimal message will come up
                errorDecimal = true;
            }
            
        }
   
        // ---------------------------- TITLE SCREEN ---------------------------- //
        if (isHoveringBinary && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && clearScreen == false) {
            clearScreen = true;
            printf("Debug Working Here!\n");
            displayBinary = true;
        }
        
        if (isHoveringDecimal && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && clearScreen == false) {
            clearScreen = true;
            printf("Debug Working Here Too!\n");
            displayDecimal = true;
        }
        
        if (isHoveringLangBar) {
            while (alphaLangPop < 1.0f) {
               alphaLangPop += 0.05f; // Fade-in animation
                             
            }         
        }
   
        if (isHoveringLangBar || isHoveringLangPopUp) { // Language portion
                DrawRectangleRec(langPopUp, Fade(DARKBLUE, alphaLangPop)); 
                
                // ------------------ PIXELS ------------------------- //
                
                // NORWEGIAN FLAG //
                
                // Row 1
                DrawRectangle(780, 390, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(785, 390, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 390, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(795, 390, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(800, 390, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(805, 390, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(810, 390, 5, 5, Fade(RED, alphaLangPop));
                
                // Row 2
                DrawRectangle(780, 395, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(785, 395, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 395, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(795, 395, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(800, 395, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(805, 395, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(810, 395, 5, 5, Fade(WHITE, alphaLangPop));
                
                // Row 3
                DrawRectangle(780, 400, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(785, 400, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(790, 400, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(795, 400, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(800, 400, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(805, 400, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(810, 400, 5, 5, Fade(BLUE, alphaLangPop));
                
                // Row 4
                DrawRectangle(780, 405, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(785, 405, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 405, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(795, 405, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(800, 405, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(805, 405, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(810, 405, 5, 5, Fade(WHITE, alphaLangPop));
                
                // Row 5
                DrawRectangle(780, 410, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(785, 410, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 410, 5, 5, Fade(BLUE, alphaLangPop));
                DrawRectangle(795, 410, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(800, 410, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(805, 410, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(810, 410, 5, 5, Fade(RED, alphaLangPop));
                
                DrawText("Norsk", 825, 390, 25, Fade(WHITE, alphaLangPop));
                
                // ENGLISH FLAG //
                
                // Row 1
                DrawRectangle(780, 440, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(785, 440, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 440, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(795, 440, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(800, 440, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(805, 440, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(810, 440, 5, 5, Fade(WHITE, alphaLangPop));
                
                // Row 2
                DrawRectangle(780, 445, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(785, 445, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 445, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(795, 445, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(800, 445, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(805, 445, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(810, 445, 5, 5, Fade(WHITE, alphaLangPop));
                
                // Row 3
                DrawRectangle(780, 450, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(785, 450, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(790, 450, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(795, 450, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(800, 450, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(805, 450, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(810, 450, 5, 5, Fade(RED, alphaLangPop));
                
                // Row 4
                DrawRectangle(780, 455, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(785, 455, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 455, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(795, 455, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(800, 455, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(805, 455, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(810, 455, 5, 5, Fade(WHITE, alphaLangPop));
                
                // Row 5
                DrawRectangle(780, 460, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(785, 460, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(790, 460, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(795, 460, 5, 5, Fade(RED, alphaLangPop));
                DrawRectangle(800, 460, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(805, 460, 5, 5, Fade(WHITE, alphaLangPop));
                DrawRectangle(810, 460, 5, 5, Fade(WHITE, alphaLangPop));
                
                DrawText("English", 825, 440, 25, Fade(WHITE, alphaLangPop));
                
                // ----------------------------------------------------- //
                
                DrawRectangleRec(btnNorsk, Fade(RED, invisBtnNorsk));
                DrawRectangleRec(btnEnglish, Fade(RED, invisBtnEnglish));
                
                if (isHoveringBtnNorsk && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && clearScreen == false) {
                    norwegianLang = true;
                    englishLang = false;
                    
                    // DEBUG
                    printf("norsk working");
                    fflush(stdout);
                    
                    
                } else if (isHoveringBtnEnglish && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && clearScreen == false) {
                    norwegianLang = false;
                    englishLang = true;
                    
                    // DEBUG
                    printf("english working");
                    fflush(stdout);
                    
                }
                
                if (englishLang) { // Using memcpy to overwrite the previous characters
                        memcpy(&TextBinary[0], "BINARY", 6);
                        memcpy(&TextDecimal[0], "DECIMAL", 7);
                        
                        memcpy(&title[0], "Binary & Decimal Converter", 27);
                        
                        memcpy(&binaryAsk[0], "Please enter a BINARY number to convert\n               (00000000 - 11111111)", 98);
                        memcpy(&binaryConvert[0], "CONVERT", 9);
                        memcpy(&binaryAskResult[0], "The binary equivalent to [              ] is", 48);
                        memcpy(&returnBinary[0], "PRESS [SPACE] TO RETURN", 24);
                        
                        memcpy(&decimalAsk[0], "Please enter a DECIMAL number to convert\n                       (1-255)", 89);
                        memcpy(&decimalConvert[0], "CONVERT", 9);
                        memcpy(&decimalValueException[0], "VALUE MUST BE BETWEEN [1-255]!", 31);
                        memcpy(&decimalAskRes[0], "The decimal equivalent to [      ] is", 48);
                        memcpy(&returnDecimal[0], "PRESS [SPACE] TO RETURN", 24);
                        
                        memcpy(&langText[0], "LANGUAGES", 16);
                        
                        langTextX = 790;
                        langTextY = 500;
                        langTextS = 25;
                        
                        titleX = 120;
                        TextBinaryX = 350;
                        TextDecimalX = 340;
                      
                        
                    } else if (norwegianLang) { 
    
                        memcpy(&TextBinary[0], "BINÆR", 6);
                        memcpy(&TextDecimal[0], "TITALL", 7);
                        
                        memcpy(&title[0], "Binær- & Titallskonverter", 27);
                        
                        memcpy(&binaryAsk[0], "Vennligst tast inn et BINÆRTALL\n         for å konvertere\n         (00000000 - 11111111)", 98);
                        memcpy(&binaryConvert[0], "KONVERTER", 9);
                        memcpy(&binaryAskResult[0], "Binærtallet som tilsvarer til [              ] er", 48);
                        memcpy(&returnBinary[0], "TRYKK [SPACE] TIL MENYEN", 24);
                        
                        memcpy(&decimalAsk[0], "Vennligst tast inn et TITALL\n      for å konvertere\n            (1-255)", 89);
                        memcpy(&decimalConvert[0], "KONVERTER", 9);
                        memcpy(&decimalValueException[0], "VERDIEN MÅ VÆRE MELLOM 1-255", 31);
                        memcpy(&decimalAskRes[0], "Titallet som tilsvarer til [      ] er", 48);
                        memcpy(&returnDecimal[0], "TRYKK [SPACE] TIL MENYEN", 24);
                        
                        memcpy(&langText[0], "SPRÅK", 16);
                        langTextX = 805;
                        langTextY = 495;
                        langTextS = 30;
                        
                        titleX = 125;
                        TextBinaryX = 355;
                        TextDecimalX = 345;
                    }
            }
        
        // ---------------------------- BINARY ---------------------------- //
        
        if (displayBinaryResult || displayDecimalResult) { 
            if (IsKeyPressed(KEY_SPACE)) { // Once the space key has been entered after the output sequence, everything will reset to what it was before the program initialized
                displayBinaryResult = false;
                displayDecimalResult = false;
                displayBinary = false;
                displayDecimal = false;
                binaryLen = 0;
                decimalLen = 0;
                
                memset(binaryInput, 0, sizeof(binaryInput)); 
                memset(decimalInput, 0, sizeof(decimalInput)); 
                
                clearScreen = false;  
                errorDecimal = false;
                langPop = false;
                
                alphaButtonBinary = 0.0f;
                alphaButtonDecimal = 0.0f;
                
                alphaConvertBinary = 0.0f;
                alphaOutputBinary = 0.0f;
                
                alphaConvertDecimal = 0.0f;
                alphaOutputDecimal = 0.0f;
                
                alphaLangBar = 0.0f;
                alphaLangPop = 0.0f;


            }
        }
        
        //------------------------------- DRAWING PART ----------------------------------//
        BeginDrawing();
        ClearBackground(BLUE); // Blue Background
        
        if (!clearScreen) { // Everything will be pointed to with precision
            
            // Splash screen text
            DrawText(title, titleX, titleY, titleSize, WHITE);
            
            if (titleY > 75) {
                titleY -= 1.5;
            } else {
                if (alphaButtonBinary < 1.0f) alphaButtonBinary += 0.02f; // Fade-in animation
                DrawRectangle(310, 230, 300, 75, Fade(BLACK, alphaButtonBinary)); // Binary shadow
                DrawRectangleRec(ButtonBinary, Fade(WHITE, alphaButtonBinary)); // Binary button
                DrawText(TextBinary, TextBinaryX, TextBinaryY, 50, Fade(BLACK, alphaButtonBinary)); // Binary text
                
                if (alphaButtonDecimal < 1.0f) alphaButtonDecimal += 0.02f; // Fade-in animation
                DrawRectangle(310, 360, 300, 75, Fade(BLACK, alphaButtonDecimal)); // Decimal shadow
                DrawRectangleRec(ButtonDecimal, Fade(WHITE, alphaButtonDecimal)); // Decimal button
                DrawText(TextDecimal, TextDecimalX, TextDecimalY, 50, Fade(BLACK, alphaButtonDecimal)); // Decimal text
                DrawText(Copyright, 360, 500, 20, Fade(WHITE, alphaButtonDecimal)); // Copyright text
                
                if (alphaLangBar < 1.0f) alphaLangBar += 0.02f; // Fade-in animation
                DrawRectangleRec(langBar, Fade(DARKBLUE, alphaLangBar)); // Languages text
                DrawText(langText, langTextX, langTextY, langTextS, Fade(WHITE, alphaLangBar));
                
            } 
 
           
            if (isHoveringBinary) { // When hovering on binary button
                DrawRectangleRec(ButtonBinary, Fade(LIGHTGRAY, alphaButtonBinary)); // Fades into light-gray during hover
                DrawText(TextBinary, TextBinaryX, TextBinaryY, 50, Fade(BLACK, alphaButtonBinary)); // Redraws text
            } else {
                DrawRectangleRec(ButtonBinary, Fade(WHITE, alphaButtonDecimal)); // Same for fade-out
                DrawText(TextBinary, TextBinaryX, TextBinaryY, 50, Fade(BLACK, alphaButtonBinary));
            }
            
            if (isHoveringDecimal) { // When hovering on decimal button
                DrawRectangleRec(ButtonDecimal, Fade(LIGHTGRAY, alphaButtonDecimal)); // Fades into light-gray during hover
                DrawText(TextDecimal, TextDecimalX, TextDecimalY, 50, Fade(BLACK, alphaButtonDecimal)); // Redraws text
            } else {
                DrawRectangleRec(ButtonDecimal, Fade(WHITE, alphaButtonDecimal)); // Same for fade-out
                DrawText(TextDecimal, TextDecimalX, TextDecimalY, 50, Fade(BLACK, alphaButtonDecimal));
            }
            
        } else if (displayBinary) { // When binary is displayed!
            if (!displayBinaryResult) {
                
                ClearBackground(BLUE);
                if (alphaConvertBinary < 1.0f) alphaConvertBinary += 0.04f;
                DrawRectangle(windowBinaryX+10, windowBinaryY+10, 500, 75, Fade(BLACK, alphaConvertBinary)); // Binary input shadow
                DrawRectangleRec(windowBinary, Fade(WHITE, alphaConvertBinary)); // Binary input
                
                if (englishLang && !norwegianLang) {
                    DrawText(binaryAsk, 50, 100, 40, Fade(WHITE, alphaConvertBinary)); // Main title
                    DrawRectangle(convertBinaryX+10, convertBinaryY+10, 200, 50, Fade(BLACK, alphaConvertBinary)); // Convert button shadow
                    DrawRectangleRec(convertBinary, Fade(WHITE, alphaConvertBinary)); // Convert button
                    
                    if (isHoveringConvertBinary) { // Accounts for text size change between languages
                        DrawRectangle(convertBinaryX+10, convertBinaryY+10, 200, 50, Fade(BLACK, alphaConvertBinary)); // Fades into light-gray during hover
                        DrawRectangleRec(convertBinary, Fade(LIGHTGRAY, alphaButtonBinary)); // Redraws text
                    }
                    
                    DrawText(binaryConvert, 375, 370, 35, Fade(BLACK, alphaConvertBinary)); // Convert TEXT
                    
                } else if (!englishLang && norwegianLang) {
                    DrawText(binaryAsk, 140, 100, 40, Fade(WHITE, alphaConvertBinary)); // Main title
                    DrawRectangle(convertBinaryX-10, convertBinaryY+10, 250, 50, Fade(BLACK, alphaConvertBinary)); // Convert button shadow
                    DrawRectangle(convertBinaryX-20, convertBinaryY, 250, 50, Fade(WHITE, alphaConvertBinary)); // Convert button
                    
                    if (isHoveringConvertBinary) {
                        DrawRectangle(convertBinaryX-10, convertBinaryY+10, 250, 50, Fade(BLACK, alphaConvertBinary)); // Fades into light-gray during hover
                        DrawRectangle(convertBinaryX-20, convertBinaryY, 250, 50, Fade(LIGHTGRAY, alphaButtonBinary)); // Redraws text
                        DrawRectangle(convertBinaryX-20, convertBinaryY, 250, 50, Fade(LIGHTGRAY, alphaButtonBinary)); // Duplicate for patching
                    }
                    
                    DrawText(binaryConvert, 365, 370, 35, Fade(BLACK, alphaConvertBinary)); // Convert TEXT
                }
                
                DrawText(binaryInput, 250, 260, 60, Fade(BLACK, alphaConvertBinary)); // Displays the typed numbers
                
            } else if (displayBinaryResult) {
                ClearBackground(BLUE);
                
                if (alphaOutputBinary < 1.0f) alphaOutputBinary += 0.08f; // Fade-in animation
                DrawText(binaryAskResult, 80, 150, 40, Fade(WHITE, alphaOutputBinary)); // Main title
                
                if (englishLang && !norwegianLang) {
                    DrawText(binaryInput, 630, 150, 40, Fade(RED, alphaOutputBinary)); // Displays the previously typed number
                } else if (!englishLang && norwegianLang) {
                    DrawText(binaryInput, 710, 150, 40, Fade(RED, alphaOutputBinary)); // Displays the previously typed number
                }
                DrawRectangle(outputBinaryX+10, outputBinaryY+10, 200, 75, Fade(BLACK, alphaOutputBinary)); // Display shadow
                DrawRectangleRec(outputBinary, Fade(WHITE, alphaOutputBinary)); // Display
                DrawText(outputTextBinary, 410, 250, 60, Fade(BLACK, alphaOutputBinary)); // Converted number
                
                DrawText(returnBinary, 320, 400, 20, Fade(WHITE, alphaOutputBinary)); // Small text
                
                
            }
            
        } else if (displayDecimal) {            
            ClearBackground(BLUE);
            
            if (!displayDecimalResult) {
                
                ClearBackground(BLUE);
                if (alphaConvertDecimal < 1.0f) alphaConvertDecimal += 0.04f; // Fade-in animation
                    if (englishLang && !norwegianLang) {
                        DrawText(decimalAsk, 30, 100, 40, Fade(WHITE, alphaConvertDecimal)); // Main title
                    } else if (!englishLang && norwegianLang) {
                        DrawText(decimalAsk, 190, 100, 40, Fade(WHITE, alphaConvertDecimal));
                    }
                    
                DrawRectangle(windowDecimalX+10, windowDecimalY+10, 300, 75, Fade(BLACK, alphaConvertDecimal)); // Decimal input shadow
                DrawRectangleRec(windowDecimal, Fade(WHITE, alphaConvertDecimal)); // Decimal input
                
                if (englishLang && !norwegianLang) {
                    DrawRectangle(convertDecimalX+10, convertDecimalY+10, 200, 50, Fade(BLACK, alphaConvertDecimal)); // Convert button shadow
                    DrawRectangleRec(convertDecimal, Fade(WHITE, alphaConvertDecimal)); // Convert button                    
                } else if (!englishLang && norwegianLang) {
                    DrawRectangle(convertDecimalX-10, convertDecimalY+10, 250, 50, Fade(BLACK, alphaConvertDecimal)); // Convert button shadow
                    DrawRectangle(convertDecimalX-20, convertDecimalY, 250, 50, Fade(WHITE, alphaConvertDecimal)); // Convert button
                }
               
                
                if (englishLang && !norwegianLang) {
                    DrawText(decimalConvert, 375, 370, 35, Fade(BLACK, alphaConvertDecimal)); // Convert TEXT           
                    
                    if (isHoveringConvertDecimal) {
                        DrawRectangle(convertDecimalX+10, convertDecimalY+10, 200, 50, Fade(BLACK, alphaConvertDecimal)); // Fades into light-gray during hover
                        DrawRectangleRec(convertBinary, Fade(LIGHTGRAY, alphaButtonDecimal)); // Redraws text
                        DrawText(decimalConvert, 375, 370, 35, Fade(BLACK, alphaConvertDecimal));
                    }                    
                    
                } else if (!englishLang && norwegianLang) {
                    DrawText(decimalConvert, 360, 370, 35, Fade(BLACK, alphaConvertDecimal));
                    
                    if (isHoveringConvertDecimal) {
                        DrawRectangle(convertDecimalX-10, convertDecimalY+10, 250, 50, Fade(BLACK, alphaConvertDecimal)); // Fades into light-gray during hover
                        DrawRectangle(convertDecimalX-20, convertDecimalY, 250, 50, Fade(LIGHTGRAY, alphaButtonDecimal)); // Redraws text
                        DrawText(decimalConvert, 360, 370, 35, Fade(BLACK, alphaConvertDecimal));
                    }
                }
              
                
                DrawText(decimalInput, 330, 260, 60, Fade(BLACK, alphaConvertDecimal)); // Shows the typed number
                
                if (errorDecimal && englishLang && !norwegianLang) {
                    DrawText(decimalValueException, 280, 450, 20, Fade(YELLOW, alphaConvertDecimal)); // Error with small text for overflowing values
                } else if (errorDecimal && !englishLang && norwegianLang) {
                    DrawText(decimalValueException, 300, 450, 20, Fade(YELLOW, alphaConvertDecimal)); // Error with small text for overflowing values
                }
                
                
            } else if (displayDecimalResult) {
                ClearBackground(BLUE);
               
                
                if (alphaOutputDecimal < 1.0f) alphaOutputDecimal += 0.08f; // Fade-in animation
                    if (englishLang && !norwegianLang) {
                        DrawText(decimalAskRes, 80, 150, 40, Fade(WHITE, alphaOutputDecimal)); // Main title                        
                    } else if (!englishLang && norwegianLang) {
                        DrawText(decimalAskRes, 110, 150, 40, Fade(WHITE, alphaOutputDecimal));
                    }

                DrawText(decimalInput, 650, 150, 40, Fade(RED, alphaOutputDecimal)); // Previously typed in number
                
                DrawRectangle(outputDecimalX+10, outputDecimalY+10, 500, 75, Fade(BLACK, alphaOutputDecimal)); // Display shadow
                DrawRectangleRec(outputDecimal, Fade(WHITE, alphaOutputDecimal)); // Display
                DrawText(outputTextDecimal, 250, 260, 60, Fade(BLACK, alphaOutputDecimal)); // Converted number
                
                DrawText(returnDecimal, 320, 400, 20, Fade(WHITE, alphaOutputDecimal)); // Small text
                   
            }
        }
            
        EndDrawing();

    }
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
