Ohjelma on tarkoitettu lentokoneen osien ja tarvikkeiden varastoinnin hallintaan. Siinä voi luoda, ottaa, muokata ja etsiä vastossa olevia osia.
Ohjelma käsittelee kolmea eri osatyyppiä:

CONSUMABLE (C):
Kulutustarvikkeita kuten: teipit, kiinnikkeet, maalit ja kemikaalit.

ROTABLE (R):
Varaosia joista jokaisella yksilöllä on sarjanumero ja ovat osa huoltokiertoa, eli vikaantumisen jälkeen yksilö voidaan palauttaa käyttöön korjauksen jälkeen.
esimerkiksi: moottorit, tietokoneet, penkit, ovet ja ohjainpinnat.

CONSUMABLE REPAIRABLE (E):
Vähemmän lentoturvallisuuden kannalta kriittisä osia, joilla ei välttämättä ole sarjanumeroa, mutta niitä on sallittu korjata.


KÄYTTÖ:
Ohjelman päävalikosta voit valita haluamasi toiminnon.
Mikäli haluat lisätä varastoon uuden osan, valitsemalla "ADD ITEM TO THE WAREHOUSE" ohjelma aloittaa osan luonnin ja ohjeistaa käyttäjän prosessin läpi.
Mikäli haluat muokata tai ottaa varastossa olevia osia, kannattaa aloittaa "SEARCH ITEMS" toiminnosta, josta saat tarvitsemasi varastokoodit muokattaville osille.
Varastokoodi näkyy hakutoiminnossa osan nimen vieressä ja se luodaan automaattisesti osan luonnin yhteydessä typpin mukaan (C, R tai E alkuisena).


TOIMINTA:
Ohjelmassa on luokka "item", joka sisältää osien käsittelyyn liittyvät funktiot ja parametrit. Jokaiselle osatyypille on myös oma alaluokka "types" tiedostossa, joka hoittaa
osien luonnin kullekkin osatyypille sopivalla tavalla. Alaluokat on myös tallennettu omiin vektoreihin: vec_c, vec_r ja vec_e. 
Ohjelma hoitaa myös osien kopionnin "Items.txt" tiedostoon, josta se myös lukee osat ohjelman käynnistyessä. Ohjelma kirjoittaa tiedostoa aina kun osiin tehdään muutoksia,
jotta osat pysyisi tallessa vaikka ohjelma suljettaisiin kesken suorituksen.
