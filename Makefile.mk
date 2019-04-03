bin/KaradocBank : src/KaradocBank.c lib/Compte.o lib/KaradocUtil.o lib/TitulaireCompte.o lib/Virement.o
	gcc src/KaradocBank.c -o bin/KaradocBank lib/KaradocUtil.o lib/Compte.o lib/TitulairesCompte.o lib/Virement.o

lib/Compte.o : src/Compte.c
	gcc -c src/Compte.c -o lib/Compte.o

lib/KaradocUtil.o : src/KaradocUtil.c
	gcc -c src/KaradocUtil.c -o lib/KaradocUtil.o

lib/TitulaireCompte.o : src/TitulaireCompte.c
	gcc -c src/TitulaireCompte.c -o lib/TitulaireCompte.o

lib/Virement.o : src/Virement.c
	gcc -c src/Virement.c -o lib/Virement.o