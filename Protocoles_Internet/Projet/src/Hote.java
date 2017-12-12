import java.net.*;
import java.io.*;
import java.util.*;
import javafx.stage.Stage;
import javafx.application.Application;

public class Hote extends Conv implements Runnable{
	
	public Hote(int p){
		super(null,p);
	}
	
	
	public void run(){
		Thread t=null;
		try{
			System.out.println("Hote en attente sur le port "+this.port);
			ServerSocket server = new ServerSocket(this.port);
			while(true){
				Socket s=server.accept();
				this.socket = s;
				System.out.println("Connexion en cours...");
				Conversation c = new Conversation(this);
				t = new Thread(c);
				t.start();
				t.join();
				s.close();
				server.close();
				break;
			}
		}
		catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
			if(t!=null){t.stop();}
		}
	}


}
