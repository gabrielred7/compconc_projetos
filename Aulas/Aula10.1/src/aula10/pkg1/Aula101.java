/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Leitores e escritores usando monitores em Java */
/* -------------------------------------------------------------------*/

package aula10.pkg1;

public class Aula101 {
    static final int L = 4;
    static final int E = 3;
    
    public static void main(String[] args) {
        int i;
        LeitorEscritor monitor = new LeitorEscritor(); // Monitor (objeto compartilhado entre leitores e escritores)
        Leitor[] ler = new Leitor[L]; // Threads leitores
        Escritor[] escrever = new Escritor[E]; // Threads escritores
    
        //inicia o log de saida
        System.out.println ("import verificaLE");
        System.out.println ("le = verificaLE.LE()");
        
        for (i=0; i<L; i++) {
            ler[i] = new Leitor(i+1, (i+1)*500, monitor);
            ler[i].start(); 
        }
    
        for (i=0; i<E; i++) {
            escrever[i] = new Escritor(i+1, (i+1)*500, monitor);
            escrever[i].start(); 
        }
    }
}