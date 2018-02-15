package senac.poo.aula2;

/**
 * @author roger.fgalmeida
 */
public class ContaBancaria {
    
    int numeroconta;
    String nome;
    double saldo;
    double limite;
    
    void deposito ( double quantidade) {
        
        this.saldo += quantidade;
    }
    void saque ( double quantidade) {
        
        this.saldo -= quantidade;
    }
    void transferencia ( double quantidade){
        
    }
}
