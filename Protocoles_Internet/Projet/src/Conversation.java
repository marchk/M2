import java.io.*;
import java.lang.*;
import java.net.*;
import java.util.*;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
 
public class Conversation extends JFrame implements Runnable ,ActionListener{
	private Conv h;
	private JLabel[] lab_tab;
	private JButton envoi;
	private JTextField textField;
	private PrintWriter pw;
	
	public Conversation(Conv v){
		this.h = v;
    	this.setTitle("Connection with "+h.getSock().getInetAddress().toString()+" in port "+h.getPort());
    	this.setSize(700, 500);
    	this.setLocationRelativeTo(null);
	    this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	    // Create a  vertical box
		Box vBox = Box.createVerticalBox();
		
		lab_tab = new JLabel[10];
		for(int i=0; i<10; i++){
			JLabel label = new JLabel("Label "+(i+1));
			lab_tab[i] = label;
			label.setSize(700,500/11);
			vBox.add(label);
			vBox.add(Box.createVerticalGlue());
		}
		
		textField = new JTextField();
		textField.setSize(600, 500/11);
        JScrollPane scrollPane = new JScrollPane(textField);
        
        envoi = new  JButton("Send");
        //envoi.setSize(20,100);
        envoi.addActionListener(this);
	    Box hBox = Box.createHorizontalBox();
		hBox.add(textField); 
		hBox.add(Box.createHorizontalGlue()); 
		hBox.add(envoi);
		
		JPanel hPanel = new JPanel();
    	BoxLayout boxLayout = new BoxLayout(hPanel, BoxLayout.Y_AXIS);
    	hPanel.add(vBox);
    	hPanel.add(hBox);
    	hPanel.setLayout(boxLayout);
		
		Container contentPane = this.getContentPane();
		contentPane.add(hPanel, BorderLayout.SOUTH);
    	this.pack();
	    
	    
	    
	    
	    try{
			pw = new PrintWriter(new OutputStreamWriter(h.getSock().getOutputStream()));
		}catch(Exception e){
		
		}
		
  }
  
   public void actionPerformed(ActionEvent evt) {
        String text = textField.getText();
        maj(this.lab_tab, text);
        textField.setText("");
        pw.println(text);
        pw.flush();
   }
       
   private synchronized static void maj(JLabel[] lb, String s){
		for(int i=0; i<lb.length-1; i++){
			lb[i].setText(lb[i+1].getText());
		}
		lb[lb.length-1].setText(s);
	}
  
	public void run(){
		ConvReception cv = new ConvReception(this.h.getSock(),this.lab_tab);
		Thread t = new Thread(cv);
		t.start();
	  	this.setVisible(true);
	}
	
}

