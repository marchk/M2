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
	}
	
	public void run(){
		Socket s=null;
		Exception ex=null;
		int i=0;
		try{
			do{
				try{
					s=new Socket(this.ip,this.port);
					i++;
				}catch(Exception e){ex = e;}
			}while(ex!=null && i<0xfffffff);
			this.socket = s;
			System.out.println("Connexion établie");
			Conversation c = new Conversation(this);
			/*t = new Thread(c);
			t.start();*/
			//s.close();
			//server.close();
		}catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}


}
