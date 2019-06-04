#pragma once

class Markov
{
  public:
    void create(std::string& file, unsigned int suffixLen, unsigned int words, const std::string name);

  private:
    std::string createText(int w);
    void createDictionary(unsigned int suffixLen);
    std::string buffer;
    std::map<std::string, std::vector<std::string>> dictionary;
};
