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
		try{
			Socket s=new Socket(this.ip,this.port);
			this.socket = s;
			Conversation c = new Conversation(this);
			Thread t = new Thread(c);
			t.start();
		}catch(Exception e){
			System.out.println(e);
			e.printStackTrace();
		}
	}


}
