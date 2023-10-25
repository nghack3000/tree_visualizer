#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "redYellowNode.h"


class RYVisualizer {
    RYNode* root;
public:
    void drawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, Color color) {
        int numSegments = 100;
        double angleIncrement = 2 * M_PI / numSegments;
        SDL_Color sdlColor;

        if (color == Color::RED) {
            sdlColor = { 255, 0, 0, 255 };
        }
        else {
            sdlColor = { 255, 255, 0, 255 };
        }

        SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);

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

    void renderRYT(SDL_Renderer* renderer, TTF_Font* font, RYNode* root, int x, int y, int level, int levelSpacing, SDL_Color lineColor) {
        if (root) {
            // Render data inside the circle
            SDL_Color textColor = { 255, 255, 255, 255 };
            std::string dataStr = std::to_string(root->data);

            SDL_Surface* textSurface = TTF_RenderText_Solid(font, dataStr.c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            SDL_Rect textRect = { x - NODE_RADIUS / 2, y - NODE_RADIUS / 2, textSurface->w, textSurface->h };

            // Draw the node
            drawCircle(renderer, x, y, NODE_RADIUS, root->color);
            SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

            // Cleanup text resources
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);

            SDL_RenderPresent(renderer);
            SDL_Delay(ANIMATION_DELAY_MS);

            // Recursively render children
            if (root->left && (root->left->left != NULL || root->left->right != NULL)) {
                int childX = x - levelSpacing;
                int childY = y + 100;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY);
                drawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS, lineColor);
                renderRYT(renderer, font, root->left, childX, childY, level + 1, levelSpacing / 2, lineColor);
            }

            if (root->right && (root->left->left != NULL || root->left->right != NULL)) {
                int childX = x + levelSpacing;
                int childY = y + 100;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x, y + NODE_RADIUS, childX, childY);
                drawLine(renderer, x, y + NODE_RADIUS, childX, childY - NODE_RADIUS, lineColor);
                renderRYT(renderer, font, root->right, childX, childY, level + 1, levelSpacing / 2,lineColor);
            }
        }
    }


};

