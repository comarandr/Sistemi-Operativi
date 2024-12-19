### Esercizi Lezione bash

###### soluzioni lezione 1
qual è il pathname della home directory? `~` oppure `/home/user`, per spostarsi basta `$cd` 

visualizzare i file della home directory ordinati in base alla data di ultima modifica: `ls -t`

Che differenza c'è tra i comandi `cat`,`more`,`tail`?  

+ `cat` serve a concatenare i file  
+ `more` è un filtro che serve a visualizzare su schermo un flusso di testo una pagina per volta  
+ `tail` stampa su standard output le ultime 10 righe dei file forniti come argomenti  

esercizio link (...)

Elenco delle subdirectory contenute ricorsivamente nella vostra home:

    cd
    ls -R

modi per creare un file

- usare un editor  
- `touch [nome_file]`  
- `cat > nome_file` oppure `cat - > nome_file`  

commenta i seguenti comandi

    $ cd
    $ mkdir d1
    $ chmod 444 d1
    $ cd d1

###### Soluzioni lezione 2

pipeline per copiare il contenuto della directory _dir1_ in *dir2*: 
+ dir2 non esiste: `cp -r dir1 dir2`  
+ dir2 esiste: `cp /r dir1/* dir2`

contare numero file ricorsivamente in una cartella: `$ find /home | wc -l`
nota: se usassi `$ ls -R | wc -l` non funzionerebbe perché `ls -R` genera anche linee vuote. Inoltre meglio usare `-l` rispetto a `-w` perché file con uno spazio nel nome altererebbero il conteggio. 

lista dei file della home directory il cui nome è una stringa di 3 caratteri seguita da una cifra: `$ ls ~/???[0/9]`, per evitare le directory posso usare opzione `/d` : `$ ls -d ~/???[0/9]`

### Osservazioni interessanti

```
file1.txt
    Ciao, come stai? Io tutto bene. Spero valga lo stesso anche per te

file2.txt
    Bella, io sto una meraviglia.
```

`$ cat file1.txt file2.txt`
```
    Ciao, come stai? Io tutto bene. Spero valga lo stesso anche per te
    Bella, io sto una meraviglia.
``` 
 

