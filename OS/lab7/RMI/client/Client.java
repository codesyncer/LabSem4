import java.rmi.*;
import java.rmi.*;

public class Client {
public static void main(String args[]){
        try{
                String ip = "localhost:3000";
                Calc calc=(Calc)Naming.lookup("rmi://"+ip+"/calc");
                System.out.println(calc.add(3,14));
                System.out.println(calc.sub(62,8));
                System.out.println(calc.mul(2, 71));

        }catch(Exception e) {
                System.out.println(e);
        }
}
}
// java Client
