from bs4 import BeautifulSoup
import bs4
import urllib.request as urlib
import re
import requests
import sys

def write_lyrics(artist):
	url = 'https://google.com/search?q='
	l = []
	html = urlib.urlopen('https://paroles2chansons.lemonde.fr/paroles-'+ artist).read()
	soup = BeautifulSoup(html, features="html.parser")
	list_songs = soup.findAll("li", {"class": "item clearfix"})

	for song in list_songs:
		for a in song.find_all('a', href=True):
			l.append(a.contents[0])

	for i in range(10):
		response  = requests.get(url + artist + " " + l[i] + " lyrics")
		soup = BeautifulSoup(response.text, 'lxml')
		list_lines = soup.findAll("div", {"class": "BNeawe tAd8D AP7Wnd"})
		lyrics = ""
		for line in list_lines:
			if isinstance(line.contents[0], bs4.element.NavigableString):
				lyrics += str(line.contents[0])

		lyrics = re.sub(r' +', ' ', lyrics)
		lyrics = re.sub(r'\n+', ' ', lyrics)
		f = open("resources/" + artist + ".txt", "a")
		f.write(lyrics)
		if i == 9:
			f.write(" ")
		f.close()

if __name__ == "__main__":
	if len(sys.argv) == 2:
		write_lyrics(sys.argv[1])