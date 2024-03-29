#include <ctime>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "markov_chain.hh"
#include <stdio.h>

void Markov::create(std::string& file, unsigned int suffixLen, unsigned int words, const std::string name)
{
  std::ifstream f(file.c_str(), std::ios_base::in);
  buffer = std::string{std::istreambuf_iterator<char>{f}, {}};
  f.close();
  if (buffer.length() < 1)
  {
    perror("Could not open the file");
    return;
  }
  createDictionary(suffixLen);

  std::ofstream myfile;
  myfile.open("results/" + name + ".txt");
  myfile << createText(words - suffixLen);
  myfile.close();
}

std::string Markov::createText(int w)
{
  std::stringbuf sbuffer;
  std::ostream os (&sbuffer);

  std::string key, first, second;
  size_t next;
  std::map<std::string, std::vector<std::string>>::iterator it = dictionary.begin();
  std::advance(it, rand() % dictionary.size());
  key = (*it).first;
  os << key;
  while(true) {
    std::vector<std::string> d = dictionary[key];
    if(d.size() < 1)
      break;
    second = d[rand() % d.size()];
    if(second.length() < 1)
      break;
    os << " " << second;
    if( --w < 0 )
      break;
    next = key.find_first_of(32, 0);
    first = key.substr(next + 1);
    key = first + " " + second;
  }
  os << "\n";
  return sbuffer.str();
}
    
void Markov::createDictionary(unsigned int suffixLen)
{
  std::string w1, key;
  size_t wc = 0, pos, next;
  // Finding the first char which is different from the 'space' (32)
  next = buffer.find_first_not_of(32, 0);
  if(next == std::string::npos)
    return;
  // Fill the key with suffixLen words
  while(wc < suffixLen)
  {
    pos = buffer.find_first_of(' ', next);
    w1 = buffer.substr(next, pos - next);
    key += w1 + " ";
    next = buffer.find_first_not_of(32, pos + 1);
    if(next == std::string::npos )
      return;
    wc++;
  }
  // Removing the last space
  key = key.substr(0, key.size() - 1);
  while(true)
  {
    next = buffer.find_first_not_of(32, pos + 1);
    if(next == std::string::npos)
      return;
    pos = buffer.find_first_of(32, next);
    w1 = buffer.substr(next, pos - next);
    if(w1.size() < 1)
      break;
    if(std::find(dictionary[key].begin(), dictionary[key].end(), w1) == dictionary[key].end())
      dictionary[key].push_back(w1);
    key = key.substr(key.find_first_of(32) + 1) + " " + w1;
  }
}

int main( int argc, char* argv[] ) {
  srand(unsigned(time(0)));
  Markov m;
  if (argc == 1)
  {
    std::string file = std::string("./resources/alice_oz.txt");
    m.create(file, 3, 140, "tweet";
  }
  else if (argc > 1)
  {
    std::string file = std::string(argv[1]);
    m.create(file, 3, 140, argv[2]);
  }
  return 0;
}
