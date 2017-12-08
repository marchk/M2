import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



public class ConvReception implements Runnable{
	final private Socket socket;
	private JLabel[] list;

	public ConvReception(Socket s, JLabel[] l){
		this.socket = s;
		this.list = l;
	}
	
	
	private synchronized void maj(String s){
		for(int i=0; i<list.length-1; i++){
			list[i].setText(list[i+1].getText());
		}
		list[list.length-1].setText(s);
	}
	
	
	public void run(){
		BufferedReader br = null;
		try{
			br=new BufferedReader(new InputStreamReader(socket.getInputStream()));
			while(true){
				String mess=br.readLine();
				if((mess!=null)&&(!mess.equals(""))){
					String s = socket.getInetAddress().toString()+" dit :\n"+mess;
					maj(s);
				}
			}
		}
		catch(Exception e){
			if(br!=null){ try{br.close();}catch(Exception ex){} }
		}
	}
}
