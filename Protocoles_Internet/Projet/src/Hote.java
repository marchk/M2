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
		try{
			System.out.println("[En attente de connexion sur le port "+this.port+"...]");
			ServerSocket server = new ServerSocket(this.port);
			int i=0;
			while(i<0xfffff){
				Socket s=server.accept();
				this.socket = s;
				System.out.println("[Connexion en cours avec "+s.getInetAddress().toString()+"...]");
				Conversation c = new Conversation(this);
				if(c.isDone()){ return; }
			}
		}
		catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}


}
