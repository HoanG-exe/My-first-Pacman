#include "TextManager.h"

TextManager::TextManager(int fontSize) {
    font = TTF_OpenFont(FONT_NAME.c_str(), fontSize);
      if (font == nullptr) {
        printf("ERROR: Khong the tai font: %s | TTF_Error: %s\n", FONT_NAME.c_str(), TTF_GetError());
    }
    textTexture = nullptr;
    textSurface = nullptr;
}

TextManager:: ~TextManager() {
    if (font != nullptr) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (textTexture != nullptr) {
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    if (textSurface != nullptr) {
        SDL_FreeSurface(textSurface);
        textSurface = nullptr;
    }
}

int TextManager::getTextWidth() const {
    return textSurface->w;
}

void TextManager::loadRenderText(SDL_Renderer* &renderer, std::string text, SDL_Color textColor) {
    if (font == nullptr) return; 
    if (textSurface != nullptr) SDL_FreeSurface(textSurface);
    textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        printf("ERROR: Khong the render text '%s' | TTF_Error: %s\n", text.c_str(), TTF_GetError());
        return; // Dừng lại nếu không tạo được surface
    }
    if (textTexture != nullptr) SDL_DestroyTexture(textTexture);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
}

void TextManager::renderText(SDL_Renderer* &renderer, int scrPosX, int scrPosY, const int type) {
    dsRect = {scrPosX, scrPosY, textSurface->w, textSurface->h};
    if (type == CENTER) {
        dsRect.x = scrPosX - textSurface->w / 2;
        dsRect.y = scrPosY - textSurface->h / 2;
    }
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
}
