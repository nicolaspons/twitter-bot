#pragma once

class Markov
{
  public:
    void create(std::string& file, unsigned int suffixLen, unsigned int words);

  private:
    void createText(int w);
    void createDictionary(unsigned int suffixLen);
    std::string buffer;
    std::map<std::string, std::vector<std::string>> dictionary;
};
