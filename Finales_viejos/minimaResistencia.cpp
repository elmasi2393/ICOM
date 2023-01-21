#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minimaRes_cam(const vector<vector<int>>& M, int i, int j);  //pre-declaracion
/**
 * @brief min
 * @p retornna el valor "minimo" con el criterio de que si alguno es 0, retorna el que no es cero
 * 
 * @p la modificacion de no retornar 0 se implemento ya que era necesario para la funcion recursiva
 * @param a 
 * @param b 
 * @return int 
 */
int min(int a, int b){
	if(a == 0)
        return b;
    if(b == 0)
    	return a;
    if(a < b) 
        return a;
    return b;
}
/**
 * @brief minResistenciaTotal
 * 
 * @p devuelve la resistencia minima entre las celdas de una matriz
 * @param M 
 * @return int 
 */
int minResistenciaTotal(const vector<vector<int>>& M){
    //Busco la resistencia a partir de todas las celdas de la fila 0
    vector<int> res;
    for(int i = 0; i < M.at(0).size(); i++)
        res.push_back(minimaRes_cam(M, 0, i));

    //Una vez que tengo todos las resistencias, comparo la menor
    int minR = res.at(0);
    for(int i =1; i < res.size(); i++){
        if(res.at(i) < minR)
            minR = res.at(i);
    }
    return minR;

}
/**
 * @brief minimaRes_cam
 * 
 * @p funcion recursiva que devuelve la minima resistencia de una matriz comenzando desde una determinada celda hasta el fin de la matriz
 * @param M 
 * @param i 
 * @param j 
 * @return int 
 */
int minimaRes_cam(const vector<vector<int>>& M, int i, int j){
    if((j < 0) || (j >= M.at(0).size()))    //Si la columna se va de contorno, retorno 0
        return 0;
    if(i == M.size()-1) //Si llegue al final, tengo que devolver el valor de la celda
        return M[i][j];
    
    //chequeo hacia abajo y las diagonales
    int minA = minimaRes_cam(M, i+1, j);
    int minA_izq = minimaRes_cam(M, i+1, j+1);
    int minA_der = minimaRes_cam(M, i+1, j-1);

    //Chequeo cual es el de menor resistencia a partir de la celda actual
    int minR = min(minA, min(minA_izq, minA_der));

    return M[i][j] + minR;  //retorno el valor minimo mas el valor actual de la celda


}

int main()
{
    vector<vector<int>> M ={{2,1,3},{6,5,4},{7,8,9}};
    int a = minResistenciaTotal(M);

    cout << "Minima Resistencia Total = " << a << endl;
    return 0;
}
