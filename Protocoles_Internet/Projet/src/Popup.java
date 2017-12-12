import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
 
public class Popup extends JFrame{
	private Socket socket;
	private Popup pup;
	
	public Popup(String ip, String port, Socket s){
		this.socket = s;
    	this.setTitle("Connection with "+ip+" in port "+port);
    	this.setSize(500, 500);
    	this.setLocationRelativeTo(null);
	    this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	    pup = this;
	    JButton oui=null,non=null;
	    JLabel label = new JLabel("Souhaitez-vous entrer en connexion avec "+ip+" par le port "+port+" ?     ");
	    try{
			PrintWriter pw=new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
			oui = new JButton("OUI");
			non = new JButton("NON");
			oui.addActionListener(new ActionListener(){ 
	  			public void actionPerformed(ActionEvent e){
					pw.println("OK CON IP "+ip+" PORT "+port);
					pw.flush();
					pup.setVisible(false);
					Hote h = new Hote(Integer.parseInt(port));
					Thread tc = new Thread(h);
					tc.start();
					
	  			} 
			});
		
			non.addActionListener(new ActionListener(){ 
	  			public void actionPerformed(ActionEvent e){
					pw.println("NON CON IP "+ip);
					pw.flush();
					pup.setVisible(false);
	  			} 
			});
		}catch(Exception e){System.out.println("ERREUR"); e.printStackTrace();}
	    
	    Box hBox = Box.createHorizontalBox();
		hBox.add(oui); 
		hBox.add(Box.createHorizontalGlue()); 
		hBox.add(non);
	    
	    JPanel hPanel = new JPanel();
    	BoxLayout boxLayout = new BoxLayout(hPanel, BoxLayout.Y_AXIS);
    	hPanel.add(label);
    	hPanel.add(hBox);
    	hPanel.setLayout(boxLayout);
		
		Container contentPane = this.getContentPane();
		contentPane.add(hPanel, BorderLayout.SOUTH);
    	this.pack();
    	this.setVisible(true);
    }
    
}
