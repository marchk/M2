import java.net.*;
import java.io.*;
import java.util.*;
import javafx.stage.Stage;
import javafx.application.Application;

public class Client extends Conv implements Runnable{
	String ip;
	
	public Client(int p, String i){
		super(null,p);
	}
	
	public void run(){
		Thread t=null;
		try{
			Socket s=new Socket(this.ip,this.port);
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
			if(t!=null){t.stop();}
		}
	}


}
