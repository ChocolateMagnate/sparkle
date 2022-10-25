/* Apache 2 License | Sparkle Authors, all rights reserved.
 * This file is responsible for implementing wrapping around 
 * Common Language Representation and converting it to natural languages.*/
#include <optional>
#include "Wrapper.hpp"
#define append push_back
namespace sparkle {
    /// @brief Divides the input text into a series of text tokens consisting 
    /// of words and punctuation marks, such as colons, dots or apostrophes.
    /// @param source The input text as standard string.
    /// It can range from a single word to whole books.
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
                    ++end;
                    break;
            }
        }
        return tokens;
    }
    /// @brief Divides the input text into a series of text tokens.
    /// @param source The input text as array of characters.
    /// It can range from a single word to whole books.
    /// @return A vector of text tokens as const char*.
    std::vector<const char*> tokeniseByPunctuation(const char* source){
        std::vector<const char*> tokens;
        unsigned int start{}, end{}, index{};
        char character = *source;
        auto buffer = std::string(195, ' ');
        while (character != '\0'){
            switch (character){
                case ' ': case '\t': case '\n': case '\r': case '\f': case '\v': case ',':
                case '.': case ';': case ':': case '!': case '?': case '\"': case '\'':
                    tokens.append(buffer.c_str());
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
    /// @brief Describes the part of speech.
    enum POS {
        //Standard parts of speech:
        Noun, Verb, Adjective, Adverb, Pronoun, Preposition, Conjuction, Interjection, Numeral,
        //Language-dependent parts of speech:
        Determiner, Article, Particle, Participle, None
    };
    /// @brief Describes the tense.
    enum Tense {
        //Standard tenses
        Present, Past, Future,
        //English Tenses:
        PresentSimple, PresentContinuous, PresentPerfect, PresentPerfectContinuous, 
        PastSimple, PastContinuous, PastPerfect, PastPerfectContinuous, FutureSimple, 
        FutureContinuous, FuturePerfect, FuturePerfectContinuous, None
    };
    /// @brief Defines the word as a standalone data structure.
    class Word {
        const char* word;
        unsigned int size;
        POS partOfSpeech;
        Tense tense = Tense::None;

        public:
        Word(const char* word){
            this->word = word;
            //Dictionary initialisation.
        }
        ~Word(){}
        // Getters:
        const char* getWord() const { return word; }
        unsigned int getSize() const { return size; }
        POS getPartOfSpeech() const { return partOfSpeech; }
        Tense getTense() const { return tense; }
        // Reassingment:
        Word operator=(const char* other){
            auto newWord = Word(other);
            this->word = newWord.getWord();
            this->size = newWord.getSize();
            this->partOfSpeech = newWord.getPartOfSpeech();
            this->tense = newWord.getTense();
            return *this;
        }
        Word operator=(const Word& other){
            this->word = other.word;
            this->size = other.size;
            this->partOfSpeech = other.partOfSpeech;
            this->tense = other.tense;
            return *this;
        }
        //Two words are equal if they have the same spelling.
        bool operator==(const char* other){
            return this->word == other;
        }
        bool operator==(const Word& other){
            return this->word == other.word;
        }
        bool operator!=(const char* other){
            return this->word != other;
        }
        bool operator!=(const Word& other){
            return this->word != other.word;
        }

    };
}