# Uso di Git per il laboratorio di Algoritmi e Strutture Dati

In questo file si forniscono brevi indicazioni su come usare Git per lo
sviluppo del laboratorio di Algoritmi e Strutture Dati. Git è un sistema di
versioning del software maturo e ricco di funzionalità, qui si farà un breve
cenno alle sole funzionalità indispensabili per portare a termine quanto
richiesto dal corso, lo studente è invitato ad approfondire le parti di suo
interesse consultando il libro open source [Pro Git][].


## Configurazione Git

Git dovrebbe essere già installato e pronto per l'uso sulle macchine che
utilizzerete per il laboratorio. Prima di incominciare, solo nel caso non
abbiate  mai effettuato questa operazione in precedenza, è necessario però che
forniate a Git i dati necessari per tracciare i [commit][] che farete. Per
fare questo aprite un terminale e eseguite i seguenti comandi (nel seguito
  si assume che l'utente che digita i comandi si chiami Mario Rossi e abbia
  mail `mario.rossi@di.unito.it`):

```bash
git config --global user.name Mario Rossi
git config --global user.email mario.rossi@di.unito.it
```

Vi suggeriamo inoltre di attivare il supporto alla visualizzazione a colori dei
risultati dei comandi git. Per far ciò usate il seguente comando:

```bash
git config --global ui.color true
```

## Configurazione GitLab

Al fine di poter creare copie locali dei repository presenti su GitLab è
necessario configurare la propria macchina in modo tale che possa accedere al
repository remoto. Git permette di accedere al repository remoto sia tramite
ssh, sia tramite https.

# Accesso via ssh (laboratorio Dijkstra)

Per configurare l'accesso via ssh è necessario creare una coppia di chiavi
crittografiche e inserire la chiave pubblica tra quelle accettate dal vostro
utente su GitLab.

Per far questo accedere alla vostra pagina su GitLab e cliccate sul pulsante
 "Edit Profile settings".
Sulla pagina che si aprirà cliccate su "SSH Keys" e seguite le istruzioni
a video (in particolare siate certi di consultare la sezione che spiega come
[generare le chiavi ssh](https://gitlab.educ.di.unito.it/help/ssh/ssh.md).
Nota: in GitLab esistono due tipi di chiavi crittografiche che si possono
caricare. La chiave generica per accedere e modificare il repository e una
chiave di "Deploy" che può venire usata in sistemi di "Continuous Integration".
A voi serve seguire le istruzioni per creare quelle che sono chiamate
semplicemente chiavi "SSH".

# Accesso via https (laboratorio Dijkstra e Von Neumann)

Per accedere via https, è necessario istruire git a utilizzare il proxy dei
laboratori usando il seguente comando:

```
git config --global https.proxy username@172.16.0.254:3128
```

## Clonazione del progetto

Ognuno di voi ha a disposizione un utente su un'istanza della piattaforma gitlab
ospitata dai server del Dipartimento di Informatica. Alla piattaforma si può
accedere tramite browser aprendo l'URL:
[gitlabl.educ.di.unito.it](gitlab.educ.di.unitoit).

Una volta effettuato il login, è possibile utilizzare l'interfaccia web per
creare una copia personale del repository su cui lavorerete. Un membro per ogni
gruppo acceda all'url:
  `https://gitlab.educ.di.unito.it/esposito/laboratorioalgoritmi-2015-16`
e clicchi sull'icona "Fork repository".

Di default, l'interfaccia web proporrà di settare i permessi del repository
creato in modo tale da non permettere l'accesso a nessun altro utente che non
sia esplicitamente un membro del gruppo di sviluppatori del repository.  *Non*
cambiate questa impostazione, pena la possibilità di vedere l'elaorato annullato
perché qualcuno ne ha copiato il contenuto.

Aggiungete ora i membri del gruppo *e i docenti di laboratorio* al gruppo di
sviluppo del progetto con ruolo "developer" (trovate l'opzione seguendo i menù
Settings -> Members a partire dalla pagina del vostro repository). I nick name
dei docenti di laboratorio sono "esposito", "damfer" e "pozzato".

L'avere a disposizione una copia del laboratorio non è ancora sufficiente per
poter iniziare a lavorare: è infatti necessario creare una copia locale alla
vostra macchina. Ogni membro del gruppo di lavoro si annoti la stringa di
accesso al repository che è stato clonato: è la stringa che potete leggere in
alto a destra sulla pagina del repository che avete creato cliccando sul
pulsante "Fork repository"; notate che potete scegliere tra  la visualizzazione
della stringa di accesso ssh e https. Si effettui un clone locale alla propria
macchina aprendo un terminale e eseguendo il seguente comando:

```bash
  git clone GIT_REPO_REF
```

dove GIT_REPO_REF è la stringa menzionata di accesso menzionata.

*Nota accesso https:* la versione di git installata nei laboratori richiede di
inserire il proprio login seguito dal simbolo @ subito dopo l'indicazione del
protocollo. A titolo di esempio, riportiamo La stringa di accesso per il
repository proposto dai docenti diventa quindi (nel vostro caso dovrete
sostituire l'URL con quello che vi siete annotati precedentemente):

```
 git clone https://esposito@gitlab.educ.di.unito.it/esposito/laboratorioalgoritmi-2015-16.git
```

## Comandi di base per lavorare

Git vi permetterà di salvare il vostro lavoro e manterrà la storia delle  varie
versioni che avrete creato insieme all'indicazione di chi ha effettuato ogni
aggiornamento. Segue un elenco dei comandi principali che dovrete utilizzare:

- `status`: mostra lo stato del progetto. File  identici all'ultima versione
  salvata non vengono mostrati. File modificati, cancellati, o nuovi vengono
  visualizzati (con colori diversi se avete abilitato questa opzione).

- `log`: mostra un log dell'evoluzione del progetto. Nel caso il progetto
  sia stato clonato le informazioni includeranno la storia del progetto
  originale.

- `add`: aggiunge uno o più file alla "staging area". Il contenuto di questa
  area determinerà quali modifiche andranno a fare parte del prossimo commit. È
  necessario aggiungere esplicitamente tutti i file che sono stati modificati,
  creati o cancellati.

- `commit`: salva lo stato del progetto.

- `pull`: recupera lo stato del progetto "remoto" associato alla copia corrente
  e lo fonde con la copia attuale.

- `push`: salva le modifiche fatte al repository locale integrandole nel
  repository remoto.

Esempio di ciclo di lavoro sul repository del progetto:

```bash
git pull # mi accerto che la copia locale sia sincronizzata con quella remota

... modifiche ai file del progetto ...

git add <lista dei file modificati>
git commit -m "messaggio che descrive le modifiche apportate"
git push # aggiornamento della copia remota
```


[Pro Git]: https://progit.org
[commit]: http://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository
