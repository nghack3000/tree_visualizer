#pragma once

#include<iostream>
#include<cmath>
#include<string>
#include<SDL.h>
#include<SDL_ttf.h>

#include "avlNode.h"
#include "binaryNode.h"
#include "binaryTreeVisualizer.h"





class visualizerAVLBinary
{
    AVLNode* root;
    Node* initial_root;
public:
    void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
        int numSegments = 100;
        double angleIncrement = 2 * M_PI / numSegments;

        for (int i = 0; i < numSegments; ++i) {
            double angle = i * angleIncrement;
            double x = centerX + radius * cos(angle);
            double y = centerY + radius * sin(angle);
            SDL_RenderDrawPoint(renderer, static_cast<int>(x), static_cast<int>(y));
        }
    }
    void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, SDL_Color color) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Reset to black color
    }

    void renderTree(SDL_Renderer* renderer, TTF_Font* font, AVLNode* root, int x, int y, int level, int levelSpacing, SDL_Color lineColor) {
        if (root) {
            // Render data inside the circle
            SDL_Color textColor = { 255, 255, 255, 255 };
            SDL_Color smallFontColor = { 100, 100, 100, 255 }; // Color for small font

            std::string dataStr = std::to_string(root->data);
            std::string heightStr = "BF " + std::to_string(root->balanceFactor);
            std::string countStr = "Count: " + std::to_string(root->count);

            TTF_Font* smallFont = TTF_OpenFont("arial.ttf", 16); // Smaller font size

            SDL_Surface* textSurface = TTF_RenderText_Solid(font, dataStr.c_str(), textColor);
            SDL_Surface* heightTextSurface = TTF_RenderText_Solid(smallFont, heightStr.c_str(), smallFontColor);
            SDL_Surface* countTextSurface = TTF_RenderText_Solid(smallFont, countStr.c_str(), smallFontColor);

            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Texture* heightTextTexture = SDL_CreateTextureFromSurface(renderer, heightTextSurface);
            SDL_Texture* countTextTexture = SDL_CreateTextureFromSurface(renderer, countTextSurface);

            SDL_Rect textRect = { x - NODE_RADIUS / 2, y - NODE_RADIUS / 2, textSurface->w, textSurface->h };
            SDL_Rect heightTextRect = { x - NODE_RADIUS / 2, y - NODE_RADIUS / 2 + 20, heightTextSurface->w, heightTextSurface->h };
            SDL_Rect countTextRect = { x - NODE_RADIUS / 2, y - NODE_RADIUS / 2 + 40, countTextSurface->w, countTextSurface->h };

            // Draw the node
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawCircle(renderer, x, y, NODE_RADIUS);
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
            SDL_RenderCopy(renderer, heightTextTexture, nullptr, &heightTextRect);
            SDL_RenderCopy(renderer, countTextTexture, nullptr, &countTextRect);

            // Cleanup text resources
            SDL_FreeSurface(textSurface);
            SDL_FreeSurface(heightTextSurface);
            SDL_FreeSurface(countTextSurface);
            SDL_DestroyTexture(textTexture);
            SDL_DestroyTexture(heightTextTexture);
            SDL_DestroyTexture(countTextTexture);

            TTF_CloseFont(smallFont); // Close the smaller font

            SDL_RenderPresent(renderer);
            SDL_Delay(ANIMATION_DELAY_MS); // Introduce a delay for animation

            // Recursively render children
            if (root->left) {
                int childX = x - levelSpacing;
                int childY = y + 100;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY);
                drawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS, lineColor);
                renderTree(renderer, font, root->left, childX, childY, level + 1, levelSpacing / 2, lineColor);
            }

            if (root->right) {
                int childX = x + levelSpacing;
                int childY = y + 100;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY);
                drawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS, lineColor);
                renderTree(renderer, font, root->right, childX, childY, level + 1, levelSpacing / 2, lineColor);
            }
        }
    }

    void renderBinaryTree(SDL_Renderer* renderer, TTF_Font* font, Node* initial_root, int x, int y, int level, int levelSpacing, SDL_Color lineColor) {
        if (initial_root) {
            // Render data inside the circle
            SDL_Color textColor = { 255, 255, 255, 255 };
            std::string dataStr = std::to_string(initial_root->value);

            SDL_Surface* textSurface = TTF_RenderText_Solid(font, dataStr.c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = { x - NODE_RADIUS / 2, y - NODE_RADIUS / 2, textSurface->w, textSurface->h };

            // Draw the node
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            drawCircle(renderer, x, y, NODE_RADIUS);
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            // Cleanup text resources
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            SDL_RenderPresent(renderer);
            SDL_Delay(ANIMATION_DELAY_MS); // Introduce a delay for animation

            // Recursively render children
            if (initial_root->left) {
                int childX = x - levelSpacing;
                int childY = y + 100;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY);
                drawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS, lineColor);
                renderBinaryTree(renderer, font, initial_root->left, childX, childY, level + 1, levelSpacing / 2, lineColor);

            }

            if (initial_root->right) {
                int childX = x + levelSpacing;
                int childY = y + 100;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY);
                drawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS, lineColor);
                renderBinaryTree(renderer, font, initial_root->right, childX, childY, level + 1, levelSpacing / 2, lineColor);
            }
        }
    }

};