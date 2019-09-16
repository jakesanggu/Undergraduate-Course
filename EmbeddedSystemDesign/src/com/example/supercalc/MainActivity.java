package com.example.supercalc;

//import com.example.jnidriver.JNIDriver;
//import com.hbe.sm10m2textlcd.R;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import android.widget.Button;
import android.widget.ToggleButton;
import android.view.*;
//import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

public class MainActivity extends Activity {

	   static {
		      System.loadLibrary("calculate");
		      
		   }
	   
		   
   public native double dcalculate(String str);
   public native int issucceed();
   public native int icalculate(String str);
   public native int writestring(String str);
   public native int init();
   public native int terminate();
   public native int signal(int src, int req);
   public native void Methodadd();
   


      EditText  editText;
      EditText editText2;

      public int mode=0;
      public int error=0;
      public int flag=0;
      final int max_length = 190;
       private Button button0;
       
       
	   
       int result1;
       double result2;
       
        String txtvalue="";

       @Override
       protected void onPause(){
           super.onPause();
           terminate();
       }
       @Override
       protected void onStop(){
           super.onStop();
           terminate();
       }
       @Override
       protected void onResume(){
           super.onResume();
     //      init(0);
       }
       
       public  void mode_change(){
    	  if(mode ==0){
    		  mode = 1;
    		  signal(7,1);
    	  }
    	  else{
    		  signal(7,0);
    		  mode =0;
    	  }
    	   ui_update();
       }
       
       
       public void clear_string(){
      	 txtvalue="";
      	 ui_update();
         }
  
       
       public void change_string(String str){
    	 
    	   txtvalue = " "+str;
    	  txtvalue= txtvalue.replace("@", "sqrt_");
    	  txtvalue= txtvalue.replace(">", ">>");
    	  txtvalue= txtvalue.replace("<", "<<");
    	  txtvalue= txtvalue.replace("e", "exp_"); 
    	   ui_update();
  
       }
       
       
       public void ui_update(){
    	   
           runOnUiThread(new Runnable() {
       	    @Override
       	    public void run() {    	   
       	    	Button bt = (Button) findViewById(R.id.button30);
	    	
       	     editText.setText(txtvalue);
   	    	
       	    	if(mode == 0)
       	    		bt.setText("Integer Mode [ Click To Change ]");
       	    	else
       	    		bt.setText("Double Mode  [ Click To Change ]");
       	    	
       	    }
       	});
    	   
       }
       
       
       
   

       @Override
       public void onCreate(Bundle savedInstanceState) {
           super.onCreate(savedInstanceState);
           this.requestWindowFeature(Window.FEATURE_NO_TITLE);
           this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
           this.setContentView(R.layout.activity_main); 
           setContentView(R.layout.activity_main);
           init();
           Methodadd();
           Button bt = (Button) findViewById(R.id.button30);  
           bt.setText("Integer Mode [ Click To Change ]");
      

           editText= (EditText) findViewById(R.id.editText);
           editText2= (EditText) findViewById(R.id.editText2);

           findViewById(R.id.button1).setOnClickListener(mClickListener);
           findViewById(R.id.button2).setOnClickListener(mClickListener);
           findViewById(R.id.button3).setOnClickListener(mClickListener);
           findViewById(R.id.button4).setOnClickListener(mClickListener);
           findViewById(R.id.button5).setOnClickListener(mClickListener);
           findViewById(R.id.button6).setOnClickListener(mClickListener);
           findViewById(R.id.button7).setOnClickListener(mClickListener);
           findViewById(R.id.button8).setOnClickListener(mClickListener);
           findViewById(R.id.button9).setOnClickListener(mClickListener);
           findViewById(R.id.button10).setOnClickListener(mClickListener);
           findViewById(R.id.button11).setOnClickListener(mClickListener);
           findViewById(R.id.button12).setOnClickListener(mClickListener);
           findViewById(R.id.button13).setOnClickListener(mClickListener);
           findViewById(R.id.button14).setOnClickListener(mClickListener);
           findViewById(R.id.button15).setOnClickListener(mClickListener);
           findViewById(R.id.button16).setOnClickListener(mClickListener);
           findViewById(R.id.button17).setOnClickListener(mClickListener);
           findViewById(R.id.button18).setOnClickListener(mClickListener);
           findViewById(R.id.button19).setOnClickListener(mClickListener);
           findViewById(R.id.button20).setOnClickListener(mClickListener);
           findViewById(R.id.button21).setOnClickListener(mClickListener);
           findViewById(R.id.button22).setOnClickListener(mClickListener);
           findViewById(R.id.button23).setOnClickListener(mClickListener);
           findViewById(R.id.button24).setOnClickListener(mClickListener);
           findViewById(R.id.button25).setOnClickListener(mClickListener);
           findViewById(R.id.button26).setOnClickListener(mClickListener);
           findViewById(R.id.button27).setOnClickListener(mClickListener);
           findViewById(R.id.button28).setOnClickListener(mClickListener);
           findViewById(R.id.button29).setOnClickListener(mClickListener);
           findViewById(R.id.button30).setOnClickListener(mClickListener);
           findViewById(R.id.button31).setOnClickListener(mClickListener);
           
           
       
           
          
       }

    
       Button.OnClickListener mClickListener = new View.OnClickListener() {
           public void onClick(View view) {
        	  
        	   if(txtvalue.length() < max_length)
        	   {
        	   
        	   
               switch (view.getId()) {
                   case R.id.button10:
                      txtvalue+="0";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button1:
                      txtvalue+="1";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button2:
                      txtvalue+="2";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button3:
                      txtvalue+="3";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button4:
                      txtvalue+="4";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button5:
                      txtvalue+="5";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button6:
                      txtvalue+="6";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button7:
                      txtvalue+="7";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button8:
                      txtvalue+="8";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button9:
                      txtvalue+="9";
                      writestring(txtvalue);
                      flag = 1;
                       editText.setText(txtvalue);
                       break;
                   case R.id.button11:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " +");
                     	else
                     		txtvalue+= " +";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button12:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " -");
                     	else
                     		txtvalue+= " -";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button13:
                	if((error != 1) && flag ==0)
                      txtvalue+=(editText2.getText().toString() + " *");
                	else
                		txtvalue+= " *";
                      writestring(txtvalue);
                       editText.setText(txtvalue);
                       break;
                   case R.id.button14:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " /");
                     	else
                     		txtvalue+= " /";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button15:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " ^2");
                     	else
                     		txtvalue+= " ^2";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button16:
                      txtvalue+=" sqrt_";
                      writestring(txtvalue);
                       editText.setText(txtvalue);
                       break;
                   case R.id.button17:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " ^");
                     	else
                     		txtvalue+= " ^";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button18:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " %");
                     	else
                     		txtvalue+= " %";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button19:
                      txtvalue+="(";
                      writestring(txtvalue);
                       editText.setText(txtvalue);
                       break;
                   case R.id.button20:
                      txtvalue+=")";
                      writestring(txtvalue);
                       editText.setText(txtvalue);
                       break;
                   case R.id.button21:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " &");
                     	else
                     		txtvalue+= " &";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button22:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " |");
                     	else
                     		txtvalue+= " |";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button23:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " <<");
                     	else
                     		txtvalue+= " <<";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button24:
                	   if((error != 1) && flag ==0)
                           txtvalue+=(editText2.getText().toString() + " >>");
                     	else
                     		txtvalue+= " >>";
                           writestring(txtvalue);
                            editText.setText(txtvalue);
                            break;
                   case R.id.button25:
                      txtvalue+=" ~";
                      writestring(txtvalue);
                       editText.setText(txtvalue);
                       break;
                   case R.id.button26:
                      txtvalue+=" exp_";
                      writestring(txtvalue);
                       editText.setText(txtvalue);
                       break;
                   case R.id.button27:
                      txtvalue = "";
                      writestring(txtvalue);
                      editText.setText(txtvalue);
                       break;
                   case R.id.button28:
                      if (txtvalue.length() > 0) {
                            txtvalue = txtvalue.substring(0, txtvalue.length()-1);
                          }
                      writestring(txtvalue);
                      editText.setText(txtvalue);
                       break;
                   case R.id.button29:
                    //여기 상구 함수 들어가서 결과 받아서 출력
                      if(mode ==1)
                      {
                    	
                      double a=dcalculate(txtvalue);
                      if(issucceed()== 1)
                      {
                      error =0; flag =0;
                      txtvalue = "";
                      editText.setText(txtvalue);
                      editText2.setText(Double.toString(a));
                      writestring(Double.toString(a));
                      }
                      else{
                    	  error=1; flag = 0;
                    	  txtvalue = "";
                          editText.setText(txtvalue);
                          editText2.setText("Error");
                    	  
                      }
                  
                      }
                      
                      else if(mode==0)
                      {
                    	  int a=icalculate(txtvalue);
                    	  if(issucceed()== 1)
                          {
                    		  error =0; flag =0;
                              txtvalue = "";
                              editText.setText(txtvalue);
                              editText2.setText(Integer.toString(a));
                              writestring(Integer.toString(a));
                          }
                    	  else{
                    		  error=1; flag = 0;
                    		    txtvalue = "";
                                editText.setText(txtvalue);
                                editText2.setText("Error");
                    		  
                    	  }
                         
                         
                      } 
                      break;
                   case R.id.button30:
                      if(mode==1)
                      {
                    	  Button bt = (Button) findViewById(R.id.button30);
                    	 bt.setText("Integer Mode [ Click To Change ]");
                         mode =0;
                         signal(7,0);
                      }
                      else if(mode ==0)
                      {
                    	  Button bt = (Button) findViewById(R.id.button30);
                    	  bt.setText("Double Mode  [ Click To Change ]");
                         mode =1;
                         signal(7,1);
                      }
                      break;
                   case R.id.button31:
                      txtvalue+=".";
                      writestring(txtvalue);
                       editText.setText(txtvalue);
               }
           }
           }
       };

       
    
       
       
   }