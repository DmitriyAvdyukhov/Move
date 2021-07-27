#pragma once

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

template <typename TokenForwardIt>
TokenForwardIt FindSentenceEnd(TokenForwardIt tokens_begin, TokenForwardIt tokens_end) 
{
    const TokenForwardIt before_sentence_end
        = adjacent_find(tokens_begin, tokens_end, [](const auto& left_token, const auto& right_token) 
            {
        return left_token.IsEndSentencePunctuation() && !right_token.IsEndSentencePunctuation();
            });
    return before_sentence_end == tokens_end ? tokens_end : next(before_sentence_end);
}

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
    vector<Sentence<Token>> result;
    result.reserve(tokens.size());
    for (auto it_begin = tokens.begin(); it_begin != tokens.end(); )
    {
        auto it_find = FindSentenceEnd(it_begin, tokens.end());        
        result.push_back({make_move_iterator(it_begin), make_move_iterator(it_find) });
        it_begin = it_find;
    }
    return result;
}



struct TestToken
{
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const 
    {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const 
    {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token)
{
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting()
{
    assert(SplitIntoSentences(vector<TestToken>({ {"Split"s}, {"into"s}, {"sentences"s}, {"!"s} }))
        == vector<Sentence<TestToken>>({ {{"Split"s}, {"into"s}, {"sentences"s}, {"!"s}} }));

    assert(SplitIntoSentences(vector<TestToken>({ {"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true} }))
        == vector<Sentence<TestToken>>({ {{"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true}} }));

    assert(SplitIntoSentences(vector<TestToken>(
        { {"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true}, {"!"s, true}, {"Without"s}, {"copies"s}, {"."s, true} }))
        == vector<Sentence<TestToken>>({
            {{"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true}, {"!"s, true}},
            {{"Without"s}, {"copies"s}, {"."s, true}},
            }));
    assert(SplitIntoSentences(vector<TestToken>(
        { {"Красиво"s}, {"ты"s}, {"вошла"s}, {"в"s}, {"мою"s}, {"грешную"s}, {"жизнь"s}, {"!"s, true}, {"Красиво"s}, {"ты"s}, {"ушла"s}, {"из"s}, {"неё"s}, {"."s, true} }))
        == vector<Sentence<TestToken>>({
            {{"Красиво"s}, {"ты"s}, {"вошла"s}, {"в"s}, {"мою"s}, {"грешную"s}, {"жизнь"s}, {"!"s, true}},
            {{"Красиво"s}, {"ты"s}, {"ушла"s}, {"из"s}, {"неё"s}, {"."s, true}},
            }));
}

void TestSplitting1()
{
    assert(SplitIntoSentences(vector<TestToken>({ {"Split"s}, {"into"s}, {"sentences"s}, {"!"s} }))
        == vector<Sentence<TestToken>>({ {{"Split"s}, {"into"s}, {"sentences"s}, {"!"s}} }));

    assert(SplitIntoSentences(vector<TestToken>({ {"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true} }))
        == vector<Sentence<TestToken>>({ {{"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true}} }));

    assert(SplitIntoSentences(vector<TestToken>(
        { {"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true}, {"!"s, true}, {"Without"s}, {"copies"s}, {"."s, true} }))
        == vector<Sentence<TestToken>>({
            {{"Split"s}, {"into"s}, {"sentences"s}, {"!"s, true}, {"!"s, true}},
            {{"Without"s}, {"copies"s}, {"."s, true}},
            }));
    assert(SplitIntoSentences(vector<TestToken>(
        { {"Красиво"s}, {"ты"s}, {"вошла"s}, {"в"s}, {"мою"s}, {"грешную"s}, {"жизнь"s}, {"!"s, true}, {"Красиво"s}, {"ты"s}, {"ушла"s}, {"из"s}, {"неё"s}, {"."s, true} }))
        == vector<Sentence<TestToken>>({
            {{"Красиво"s}, {"ты"s}, {"вошла"s}, {"в"s}, {"мою"s}, {"грешную"s}, {"жизнь"s}, {"!"s, true}},
            {{"Красиво"s}, {"ты"s}, {"ушла"s}, {"из"s}, {"неё"s}, {"."s, true}},
            }));
}