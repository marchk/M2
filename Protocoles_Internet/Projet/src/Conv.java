import java.net.*;
import java.io.*;
import java.util.*;
import javafx.stage.Stage;
import javafx.application.Application;

public class Conv{
	protected int port;
	protected Socket socket;
	
	public Conv(Socket s, int p){
		this.port = p;
		this.socket = s;
	}
	
	Socket getSock(){ return this.socket; }
	
	int getPort(){ return this.port; }


}
