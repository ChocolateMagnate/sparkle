/* Apache 2 License | Sparkle Authors, all rights reserved.
 * This file is responsible for implementing wrapping around 
 * Common Language Representation and converting it to natural languages.*/
#include "Wrapper.hpp"
#define append push_back
namespace sparkle {
    /// @brief Divides the input text into a series of text tokens consisting 
    /// of words and punctuation marks, such as colons, dots or apostrophes.
    /// @param source The input text as standard string. It can range from a single word to whole books.
    /// @return A vector of text tokens as const char*.
    std::vector<const char*> tokeniseByPunctuation(std::string& source){
        std::vector<const char*> tokens;
        unsigned int start{}, end{};
        for (char character : source){
            switch (character){
                case ' ': case '\t': case '\n': case '\r': case '\f': case '\v': case ',':
                case '.': case ';': case ':': case '!': case '?': case '\"': case '\'': case '`':
                    tokens.append(source.substr(start, end).c_str());
                    start = end + 1;
                    ++end;
                    break;
                default:
                    end++;
                    break;
            }
        }
        return tokens;
    }
    /// @brief Divides the input text into a series of text tokens.
    /// @param source The input text as array of characters. It can range from a single word to whole books.
    /// @return A vector of text tokens as const char*.
    std::vector<const char*> tokeniseByPunctuation(const char* source){
        //TODO: Expand the function to words longer than 195 characters, such as chemistry terms.
        std::vector<const char*> tokens;
        unsigned int start{}, end{}, index{};
        char character = *source;
        char buffer[195]; 
        while (character != '\0'){
            switch (character){
                case ' ': case '\t': case '\n': case '\r': case '\f': case '\v': case ',':
                case '.': case ';': case ':': case '!': case '?': case '\"': case '\'':
                    tokens.append(buffer);
                    start = end + 1;
                    index = 0;
                    break;
                default:
                    buffer[index] = character;
                    ++index; ++end;
                    break;
            }
            character = *(source + end);
        }
        return tokens;
    }
}