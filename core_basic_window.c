/*******************************************************************************************
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

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
    char TextBinary[8] = "BINARY";
    
    // Decimal button settings
    float ButtonDecimalX = 300;
    float ButtonDecimalY = 350;
    Rectangle ButtonDecimal = {ButtonDecimalX, ButtonDecimalY, 300, 75};
    
    float alphaButtonDecimal = 0.0f;
    
    // Decimal text
    float TextDecimalX = 340;
    float TextDecimalY = 365;
    char TextDecimal[8] = "DECIMAL";
    
    // ----------------- BINARY - SCREEN ---------------------------- //
    
    float windowBinaryX = 220;
    float windowBinaryY = 250;
    Rectangle windowBinary = {windowBinaryX, windowBinaryY, 500, 75};
    
    float convertBinaryX = 360;
    float convertBinaryY = 360;
    Rectangle convertBinary = {convertBinaryX, convertBinaryY, 200, 50};
    
    float alphaConvertBinary = 0.0f;
    
    float outputBinaryX = 360;
    float outputBinaryY = 240;
    Rectangle outputBinary = {outputBinaryX, outputBinaryY, 200, 75};
    
    float alphaOutputBinary = 0.0f;
    
    // ------------------- DECIMAL - SCREEN -------------------------- //

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
    
    // --------------------- MISCELLANEOUS ------------------------ //
    
    char Copyright[64] = "© 2025 - Elevens";
    
    char title[64] = "Binary & Decimal Converter";

    InitWindow(screenWidth, screenHeight, "Binary & Decimal Converter");

    SetTargetFPS(60);
    
    // Transitions & Such
    bool clearScreen = false;
    
    bool displayBinary = false;
    bool displayDecimal = false;
    
    bool displayBinaryResult = false;
    bool displayDecimalResult = false;
    
    char outputTextBinary[4];
    char outputTextDecimal[9];
    
    bool errorDecimal = false;
    
    //-------------------------------- Handling user input --------------------------------//
    
    char binaryInput[9] = "";
    char decimalInput[4] = "";
    int binaryLen = 0;
    int decimalLen = 0;
    
    // Stores the binary and decimals!
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
                
                alphaButtonBinary = 0.0f;
                alphaButtonDecimal = 0.0f;
                alphaConvertBinary = 0.0f;
                alphaOutputBinary = 0.0f;
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
            }
           
            if (isHoveringBinary) {
                DrawRectangleRec(ButtonBinary, Fade(LIGHTGRAY, alphaButtonBinary)); // Fades into light-gray during hover
                DrawText(TextBinary, TextBinaryX, TextBinaryY, 50, Fade(BLACK, alphaButtonBinary)); // Redraws text
            } else {
                DrawRectangleRec(ButtonBinary, Fade(WHITE, alphaButtonDecimal)); // Same for fade-out
                DrawText(TextBinary, TextBinaryX, TextBinaryY, 50, Fade(BLACK, alphaButtonBinary));
            }
            
            if (isHoveringDecimal) {
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
                DrawText("Please enter a BINARY number to convert\n               (00000000 - 11111111)", 50, 100, 40, Fade(WHITE, alphaConvertBinary)); // Main title
                DrawRectangle(windowBinaryX+10, windowBinaryY+10, 500, 75, Fade(BLACK, alphaConvertBinary)); // Binary input shadow
                DrawRectangleRec(windowBinary, Fade(WHITE, alphaConvertBinary)); // Binary input
                
                DrawRectangle(convertBinaryX+10, convertBinaryY+10, 200, 50, Fade(BLACK, alphaConvertBinary)); // Convert button shadow
                DrawRectangleRec(convertBinary, Fade(WHITE, alphaConvertBinary)); // Convert button
                
                if (isHoveringConvertBinary) {
                    DrawRectangle(convertBinaryX+10, convertBinaryY+10, 200, 50, Fade(BLACK, alphaConvertBinary)); // Fades into light-gray during hover
                    DrawRectangleRec(convertBinary, Fade(LIGHTGRAY, alphaButtonBinary)); // Redraws text
                }
                
                DrawText("CONVERT", 375, 370, 35, Fade(BLACK, alphaConvertBinary)); // Convert TEXT
                DrawText(binaryInput, 250, 260, 60, Fade(BLACK, alphaConvertBinary)); // Displays the typed numbers
                
            } else if (displayBinaryResult) {
                ClearBackground(BLUE);
                
                if (alphaOutputBinary < 1.0f) alphaOutputBinary += 0.08f; // Fade-in animation
                DrawText("The binary equivalent to [              ] is", 80, 150, 40, Fade(WHITE, alphaOutputBinary)); // Main title
                DrawText(binaryInput, 630, 150, 40, Fade(RED, alphaOutputBinary)); // Displays the previously typed number
                
                DrawRectangle(outputBinaryX+10, outputBinaryY+10, 200, 75, Fade(BLACK, alphaOutputBinary)); // Display shadow
                DrawRectangleRec(outputBinary, Fade(WHITE, alphaOutputBinary)); // Display
                DrawText(outputTextBinary, 410, 250, 60, Fade(BLACK, alphaOutputBinary)); // Converted number
                
                DrawText("PRESS [SPACE] TO RETURN", 320, 400, 20, Fade(WHITE, alphaOutputBinary)); // Small text
                
                
            }
            
        } else if (displayDecimal) {            
            ClearBackground(BLUE);
            
            if (!displayDecimalResult) {
                
                ClearBackground(BLUE);
                if (alphaConvertDecimal < 1.0f) alphaConvertDecimal += 0.04f; // Fade-in animation
                DrawText("Please enter a DECIMAL number to convert\n                       (1-255)", 30, 100, 40, Fade(WHITE, alphaConvertDecimal)); // Main title
                DrawRectangle(windowDecimalX+10, windowDecimalY+10, 300, 75, Fade(BLACK, alphaConvertDecimal)); // Decimal input shadow
                DrawRectangleRec(windowDecimal, Fade(WHITE, alphaConvertDecimal)); // Decimal input
                
                DrawRectangle(convertDecimalX+10, convertDecimalY+10, 200, 50, Fade(BLACK, alphaConvertDecimal)); // Convert button shadow
                DrawRectangleRec(convertDecimal, Fade(WHITE, alphaConvertDecimal)); // Convert button
                
                if (isHoveringConvertDecimal) {
                    DrawRectangle(convertDecimalX+10, convertDecimalY+10, 200, 50, Fade(BLACK, alphaConvertDecimal)); // Fades into light-gray during hover
                    DrawRectangleRec(convertBinary, Fade(LIGHTGRAY, alphaButtonDecimal)); // Redraws text
                }
                
                DrawText("CONVERT", 375, 370, 35, Fade(BLACK, alphaConvertDecimal)); // Convert TEXT
                DrawText(decimalInput, 330, 260, 60, Fade(BLACK, alphaConvertDecimal)); // Shows the typed number
                
                if (errorDecimal) {
                    DrawText("VALUE MUST BE BETWEEN [1-256]!", 280, 450, 20, Fade(YELLOW, alphaConvertDecimal)); // Error with small text for overflowing values
                }
                
                
            } else if (displayDecimalResult) {
                ClearBackground(BLUE);
                
                if (alphaOutputDecimal < 1.0f) alphaOutputDecimal += 0.08f; // Fade-in animation
                DrawText("The decimal equivalent to [      ] is", 80, 150, 40, Fade(WHITE, alphaOutputDecimal)); // Main title
                DrawText(decimalInput, 650, 150, 40, Fade(RED, alphaOutputDecimal)); // Previously typed in number
                
                DrawRectangle(outputDecimalX+10, outputDecimalY+10, 500, 75, Fade(BLACK, alphaOutputDecimal)); // Display shadow
                DrawRectangleRec(outputDecimal, Fade(WHITE, alphaOutputDecimal)); // Display
                DrawText(outputTextDecimal, 250, 260, 60, Fade(BLACK, alphaOutputDecimal)); // Converted number
                
                DrawText("PRESS [SPACE] TO RETURN", 320, 400, 20, Fade(WHITE, alphaOutputDecimal)); // Small text
                   
            }
        }
            
        EndDrawing();

    }
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
