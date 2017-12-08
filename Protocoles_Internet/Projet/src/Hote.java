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
			ServerSocket server = new ServerSocket(this.port);
			while(true){
				Socket s=server.accept();
				this.socket = s;
				Conversation c = new Conversation(this);
				Thread t = new Thread(c);
				t.start();
			}
		}
		catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}


}
