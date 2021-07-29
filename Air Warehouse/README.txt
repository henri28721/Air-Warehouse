Ohjelma on tarkoitettu lentokoneen osien ja tarvikkeiden varastoinnin hallintaan. Siin� voi luoda, ottaa, muokata ja etsi� vastossa olevia osia.
Ohjelma k�sittelee kolmea eri osatyyppi�:

CONSUMABLE (C):
Kulutustarvikkeita kuten: teipit, kiinnikkeet, maalit ja kemikaalit.

ROTABLE (R):
Varaosia joista jokaisella yksil�ll� on sarjanumero ja ovat osa huoltokiertoa, eli vikaantumisen j�lkeen yksil� voidaan palauttaa k�ytt��n korjauksen j�lkeen.
esimerkiksi: moottorit, tietokoneet, penkit, ovet ja ohjainpinnat.

CONSUMABLE REPAIRABLE (E):
V�hemm�n lentoturvallisuuden kannalta kriittis� osia, joilla ei v�ltt�m�tt� ole sarjanumeroa, mutta niit� on sallittu korjata.


K�YTT�:
Ohjelman p��valikosta voit valita haluamasi toiminnon.
Mik�li haluat lis�t� varastoon uuden osan, valitsemalla "ADD ITEM TO THE WAREHOUSE" ohjelma aloittaa osan luonnin ja ohjeistaa k�ytt�j�n prosessin l�pi.
Mik�li haluat muokata tai ottaa varastossa olevia osia, kannattaa aloittaa "SEARCH ITEMS" toiminnosta, josta saat tarvitsemasi varastokoodit muokattaville osille.
Varastokoodi n�kyy hakutoiminnossa osan nimen vieress� ja se luodaan automaattisesti osan luonnin yhteydess� typpin mukaan (C, R tai E alkuisena).


TOIMINTA:
Ohjelmassa on luokka "item", joka sis�lt�� osien k�sittelyyn liittyv�t funktiot ja parametrit. Jokaiselle osatyypille on my�s oma alaluokka "types" tiedostossa, joka hoittaa
osien luonnin kullekkin osatyypille sopivalla tavalla. Alaluokat on my�s tallennettu omiin vektoreihin: vec_c, vec_r ja vec_e. 
Ohjelma hoitaa my�s osien kopionnin "Items.txt" tiedostoon, josta se my�s lukee osat ohjelman k�ynnistyess�. Ohjelma kirjoittaa tiedostoa aina kun osiin tehd��n muutoksia,
jotta osat pysyisi tallessa vaikka ohjelma suljettaisiin kesken suorituksen.
