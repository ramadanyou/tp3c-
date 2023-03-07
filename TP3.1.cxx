/*
  Exemple d'ecriture qualitative de code C++
  Application du critere 1 : lisibilite
  21 fevrier 2023
  (c) Wilfrid Lefer - UPPA
*/

#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define USAGE() { \
  printf("Usage: %s [-c] [-v] [-n <size>]\n", argv[0]); \
  exit(1); \
}

#define MAX 10

int
C_LitEntier()
{
  int n;

  do {
    n = -999999;
    scanf("%d", &n);
    if (n == -999999)
      getchar();
    else if (feof(stdin)) {
      printf("Erreur : rupture de flux avant lecture de l'ensemble des valeurs\n");
      exit(1);
    }
  } while (n == -999999);
  return n;
}

int
CPP_LitEntier()
{
  int n;
  char c;
  
  while (1) {
    cin >> n;
    if (cin.fail()) {
      if (cin.eof())
	return -1;
      cin.clear();
      do {
	c = cin.get();
      } while (c != EOF && !isdigit(static_cast<unsigned char>(c)));
      if (c == EOF)
	return EOF;
      cin.unget();
    } else break;
  }
  return n;
}

int
int_compare(const void *v1, const void *v2)
{
  int n;
  int i1=*((int *)v1);
  int i2=*((int *)v2);
  if (i1 < i2)
    n = -1;
  else if (i1 > i2)
    n = 1;
  else n = 0;
  return n;
}

int
main(int argc, char *argv[])
{
  char opt;
  int c=0;
  int n=0, *t;
  vector<int> tt;

  opt = getopt(argc, argv, "cvn:");
  while (opt != -1) {
    if (opt == 'n') {
      n = atoi(optarg);
      if (n <= 0)
	USAGE()
      else if (opt == 'c')
	c = 1;
      else if (opt == 'v')
	c = 2;
      else USAGE();
    }
    opt = getopt(argc, argv, "cvn:");
  }

  if (c == 1) {
    if (n == 0) {
      printf("Nombre de valeurs a saisir (maximum : %d) : ", MAX);
      n = C_LitEntier();
    }
    t = (int *)malloc(n*sizeof(int));
    printf("Entrez les valeurs du tableau : ");
    for (int i=0 ; i<n ; i++) {
      int v =  C_LitEntier();
      while (t[i] < 1 || t[i] > 9)
	v =  C_LitEntier();
      t[i] = v;
    }
    qsort(t, n, sizeof(int), int_compare);
    printf("Contenu du tableau :");
    for (int i=0 ; i<n ; i++)
      printf(" %d", t[i]);
    printf("\n");
  } else if (c == 0) {
    if (n == 0) {
      cout << "Nombre de valeurs a saisir (maximum : " << MAX << ") : ";
      n = CPP_LitEntier();
      while (n<1 || n>MAX) {
	cout << "Nombre de valeurs a saisir (maximum : " << MAX << ") : ";
	n = CPP_LitEntier();
      }
    }
    t = new int[n];
    cout << "Entrez les valeurs du tableau : ";
    for (int i=0 ; i<n ; i++) {
      int v =  CPP_LitEntier();
      if (t[i] < 1 || t[i] > 9) {
	if (t[i] == EOF) {
	  fprintf(stderr, "Erreur : rupture de flux avant lecture de l'ensemble des valeurs\n");
	  exit(1);
	}
      while (t[i] < 1 || t[i] > 9) {
	v =  C_LitEntier();
	if (t[i] < 1 || t[i] > 9)
	  if (t[i] == EOF) {
	    fprintf(stderr, "Erreur : rupture de flux avant lecture de l'ensemble des valeurs\n");
	    exit(1);
	  }
      }
      t[i] = v;
      }
    }
    qsort(t, n, sizeof(int), int_compare);
    cout << "Contenu du tableau : ";
    for (int i=0 ; i<n ; i++)
      cout << t[i] << " ";
    cout << endl;
  } else if (c == 2) {
    while (1) {
      int val = CPP_LitEntier();
      if (cin.eof())
	break;
      tt.push_back(val);
    }
    qsort(tt.data(), tt.size(), sizeof(int), int_compare);
    cout << "Contenu du tableau : ";
    for (int i=0 ; i<tt.size() ; i++)
      cout << tt[i] << " ";
    cout << endl;
  }
  return 0;
}
