import java.net.*;
import java.io.*;
import java.util.*;
import java.lang.*;
import javafx.stage.Stage;
import javafx.application.Application;

public class Client extends Conv implements Runnable{
	String ip;
	
	public Client(int p, String i){
		super(null,p);
		this.ip = i;
	}
	
	public void run(){
		Socket s=null;
		Exception ex=null;
		int i=0;
		try{
			System.out.println("[Tentative de connexion avec "+this.ip+" sur le port "+this.port+"...]");
			do{
				try{
					s=new Socket(this.ip,this.port);
				}catch(Exception e){ex = e;}
				System.out.println("try "+(i+1)+" : socket = "+s);
				i++;
			}while(ex!=null && i<100000);
			if(s!=null){
				this.socket = s;
				System.out.println("Connexion établie");
				Conversation c = new Conversation(this);
				/*t = new Thread(c);
				t.start();*/
				//s.close();
				//server.close();
			}
			else{ System.out.println("Connexion échouée"); }
		}catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}


}
