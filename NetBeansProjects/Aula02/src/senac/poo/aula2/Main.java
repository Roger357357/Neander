package senac.poo.aula2;

/**
 * @author roger.fgalmeida
 */
public class Main {
    
    public static void main(String[] args){
        
        ContaBancaria roger = new ContaBancaria();
        
        roger.nome = "Roger";
        roger.numeroconta = 6856;
        roger.saldo = 100.00;
        
        roger.deposito(350.00);
        System.out.println("Saldo : " +  roger.saldo);
        
        roger.saque(400);
        
    }
    
}
