#include <bits/stdc++.h>

using namespace std;

# define MAXN 1010

int N , capacidad;
int peso [ MAXN ] , valor [ MAXN ];
int dp [ MAXN ][ MAXN ]; //Aqui es donde cachearemos las respuestas

int mochila (int i , int libre ) {
	if ( libre < 0) return -100000000; //Metimos un objeto demasiado pesado
	if ( i == 0) return 0; //Si ya no hay objetos, ya no ganamos nada
	if ( dp [ i ][ libre ] != -1) return dp [ i ][ libre ]; //El DP
	//Si tomariamos el item
	int tomar = valor [ i ] + mochila ( i - 1 , libre - peso [ i ]) ;
 	//Si no tomariamos el item
	int noTomar = mochila ( i - 1 , libre ) ;
	//Devolvemos el máximo (y lo cacheamos)
	return ( dp [ i ][ libre ] = max ( tomar , noTomar ) ) ;
}
int main(){
	memset ( dp , -1 , sizeof ( dp ) ) ;//Marcamos como no calculados
	cin>>N;
	cin>>capacidad;
	for(int i=0;i<N;i++){
		int p,v;
		cin>>p>>v;
		peso[i+1]=p;
		valor[i+1]=v;
	}
	int solucion = mochila (N , capacidad) ;
	cout<<solucion;
	return 0;
}


