#version 120

uniform sampler2DRect tex0;

uniform float blurAmnty;
uniform float ff;
uniform float yw;

uniform float rw;
uniform float gw;

uniform float bw;

uniform float ll;

uniform float time;

uniform float blurAmntx;
uniform float xw;
varying vec2 texCoordVarying;

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

// Gaussian weights from http://dev.theomader.com/gaussian-kernel-calculator/

void main()
{
	vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
    
    
    //this is the array that keeps track of laplacian values
    vec2 offset[9];
    offset[0] = texCoordVarying+ vec2(-1.0*blurAmntx,-1.0*blurAmnty);
    offset[1] =  texCoordVarying+ vec2( 0.0,-1.0*blurAmnty);
    offset[2] = texCoordVarying+ vec2( 1.0*blurAmntx,-1.0*blurAmnty);
    
    offset[3] = texCoordVarying+  vec2(-1.0*blurAmntx,0.0);
    offset[4] = texCoordVarying+  vec2( 0.0,0.0);
    offset[5] = texCoordVarying+  vec2( 1.0*blurAmntx,0.0);
    
    offset[6] = texCoordVarying+  vec2(-1.0*blurAmntx,1.0*blurAmnty);
    offset[7] = texCoordVarying+  vec2( 0.0,1.0*blurAmnty);
    offset[8] = texCoordVarying+  vec2( 1.0*blurAmntx,1.0*blurAmnty);
    
    
    //here are the coordinates in the moore neighborhood
    
    
     color =texture2DRect(tex0,  offset[4]);
    vec4 c_u =texture2DRect(tex0,  offset[1]);
    vec4 c_d =texture2DRect(tex0,  offset[7]);
    vec4 c_l =texture2DRect(tex0,  offset[3]);
    vec4 c_r =texture2DRect(tex0,  offset[5]);
    
    vec4 c_ur =texture2DRect(tex0,  offset[2]);
    vec4 c_ul =texture2DRect(tex0,  offset[0]);
    vec4 c_dr =texture2DRect(tex0,  offset[8]);
    vec4 c_dl =texture2DRect(tex0,  offset[6]);
    

    
    /*

	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 4.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 3.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 2.0));
	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * 1.0));

	color += 0.382928 * texture2DRect(tex0, texCoordVarying + vec2(0.0, 0.0));

	color += 0.241732 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -1.0));
	color += 0.060598 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -2.0));
	color += 0.005977 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -3.0));
	color += 0.000229 * texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnt * -4.0));
    */
    
   // color =texture2DRect(tex0, texCoordVarying + vec2(0.0, 0.0));
  //  vec4 color_x=texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0));
   // vec4 color_y=texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0));
    
    //vec4 color_flipx=texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * -1.0, 0.0));
   // vec4 color_flipy=texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * 1.0));
    
   
    
 //   float color_bright =color.r;//
  //  float color_xbright=color_x.r;//
  //  float color_ybright=color_y.r;//

   /*this part uses rgb plus directed attenuations to determine brightness*/
   // float color_bright =rw*color.r+gw*color.g+bw*color.b;
   // float color_xbright=rw*color_x.r+gw*color_x.g+bw*color_x.b;
   // float color_ybright=rw*color_y.r+gw*color_y.g+bw*color_y.b;
    
    
    //this chunk is for the laplacian model
    vec3 color_hsb=rgb2hsv(vec3(color.r,color.g,color.b));
    
    vec3 c_u_hsb=rgb2hsv(vec3(c_u.r,c_u.g,c_u.b));
    vec3 c_d_hsb=rgb2hsv(vec3(c_d.r,c_d.g,c_d.b));
    vec3 c_l_hsb=rgb2hsv(vec3(c_l.r,c_l.g,c_l.b));
    vec3 c_r_hsb=rgb2hsv(vec3(c_r.r,c_r.g,c_r.b));
    
    vec3 c_ul_hsb=rgb2hsv(vec3(c_ul.r,c_ul.g,c_ul.b));
    vec3 c_ur_hsb=rgb2hsv(vec3(c_ur.r,c_ur.g,c_ur.b));
    vec3 c_dr_hsb=rgb2hsv(vec3(c_dr.r,c_dr.g,c_dr.b));
    vec3 c_dl_hsb=rgb2hsv(vec3(c_dl.r,c_dl.g,c_dl.b));
    
    
    float color_bright =color_hsb.z;
    float color_hue =color_hsb.x;
    float color_sat =color_hsb.y;
    
    
    
    //sum von nuemann neighborhood
    
    //brightness
    float bright_vn=c_u_hsb.z+c_d_hsb.z+c_r_hsb.z+c_l_hsb.z;
    
    //hue
    float hue_vn=c_u_hsb.x+c_d_hsb.x+c_r_hsb.x+c_l_hsb.x;
    
    //saturation
    float sat_vn=c_u_hsb.y+c_d_hsb.y+c_r_hsb.y+c_l_hsb.y;
    
    
    
    //sums moore neighborhood
    
    //brightness
    float bright_m=c_ul_hsb.z+c_dl_hsb.z+c_ur_hsb.z+c_dr_hsb.z;
    
    //hue
    float hue_m=c_ul_hsb.x+c_dl_hsb.x+c_ur_hsb.x+c_dr_hsb.x;
    
    //saturation
    float sat_m=c_ul_hsb.y+c_dl_hsb.y+c_ur_hsb.y+c_dr_hsb.y;
    
    
    
    //operations
    
    //detect and perform reaction diffusionsishthings
    
    
    /*
    
    
    if(color_hsb.z<bright_vn/4.0){
    color_bright=(1.0-yw)*color_bright+yw*bright_vn/4.0;
       //try out some nonlinearities
        
    
         // color_sat=(1.0-yw)*color_sat+yw*sat_vn/4.0;
      //   color_hue=(1.0-yw)*color_hue+yw*hue_vn/4.0;
    }
    
    
    if(color_hsb.z<bright_m/4.0){
        color_bright=(1.0-xw)*color_bright+xw*bright_m/4.0;
       
       // color_sat=(1.0-xw)*color_sat+xw*sat_m/4.0;
        //   color_hue=(1.0-xw)*color_hue+xw*hue_m/4.0;
    }
    
    
    if(color_hsb.y<sat_vn/4.0){
      //  color_bright=(1.0-yw)*color_bright+yw*bright_vn/4.0;
        //try out some nonlinearities
        
        
        color_sat=(1.0-yw)*color_sat+yw*sat_vn/4.0;
        //   color_hue=(1.0-yw)*color_hue+yw*hue_vn/4.0;
    }
    
    
    if(color_hsb.y<sat_m/4.0){
       // color_bright=(1.0-xw)*color_bright+xw*bright_m/4.0;
        
        color_sat=(1.0-xw)*color_sat+xw*sat_m/4.0;
        //   color_hue=(1.0-xw)*color_hue+xw*hue_m/4.0;
    }
    
    if(color_hsb.x<hue_vn/4.0){
        //  color_bright=(1.0-yw)*color_bright+yw*bright_vn/4.0;
        //try out some nonlinearities
        
        
        //color_sat=(1.0-yw)*color_sat+yw*sat_vn/4.0;
           color_hue=(1.0-2.0*yw)*color_hue+2.0*yw*hue_vn/4.0;
    }
    
    
    if(color_hsb.x<hue_m/4.0){
        // color_bright=(1.0-xw)*color_bright+xw*bright_m/4.0;
        
        //color_sat=(1.0-xw)*color_sat+xw*sat_m/4.0;
          color_hue=(1.0-2.0*xw)*color_hue+2.0*xw*hue_m/4.0;
    }


    
   
    //lets try keeping hue seperate and also just letting it go
    // color_hue=(1.0-2.0*yw)*color_hue+2.0*yw*hue_vn/4.0;
     //color_hue=(1.0-2.0*xw)*color_hue+2.0*xw*hue_m/4.0;
    
    
    if(color_bright==color_hsb.z){
        color_bright=color_bright*ff;
        // color_hue=color_hue*ff;
    }
    
    if(color_hue==color_hsb.x){
      
         color_hue=color_hue*ff;
    }
    
    
    color_hue=color_hue*2.0*rw;
    color_bright=color_bright*2.0*bw;
    color_sat=color_sat*2.0*gw;
    
   // color_hue=fract(color_hue);
     //color_hue=abs(color_hue);
    
    
    
    //color_bright=clamp(color_bright,0.0,1.0);
    color_bright=fract(color_bright);
    color_bright=abs(color_bright);
    
    
    color_sat=fract(color_sat);
    color_sat=abs(color_sat);
    
    
     
     
     */
     
    
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
    
    //heat diffusion
    
    
    /*
    if(color_hsb.z<(bright_m+bright_vn)/8.0){
      color_bright=(-color_bright+bright_m+bright_vn+yw)/7.0;
        //color_hue=(-color_hue+hue_m+hue_vn+yw)/7.0;
         color_sat=(-color_sat+sat_m+sat_vn+yw)/7.0;
        
      //  color_hue=(1.0-yw)*color_hue+yw*hue_vn/4.0;
        // color_hue=(1.0-xw)*color_hue+xw*hue_m/4.0;
        
        
        color_hue=(color_hue+color_bright)/2.0;
    }
   
    
    color_hue=(1.0-yw)*color_hue+yw*c_d.x;
    color_hue=(1.0-xw)*color_hue+xw*c_r.x;
 
    
    color_hue=color_hue*2.0*rw;
    color_bright=color_bright*2.0*bw;
    color_sat=color_sat*2.0*gw;
  
    
    if(color_bright>1.0){
        color_bright=1.0-(fract(color_bright));
    }
    if(color_bright<0.0){
        color_bright=1.0-(abs(color_bright));
    }
    if(color_bright>=color_hsb.z){
        color_bright=color_bright*ff;
        // color_hue=color_hue*ff;
    }
    
    if(color_hue==color_hsb.x){
       
         color_hue=color_hue*ff;
    }
   
    
    
     //maybe for heat diffusion instead of wrapping around bounce back and forth
 
    
    //if(color_hue>1.0){
      //  color_hue=1.0-(fract(color_hue));
    //}
     
    if(color_sat>1.0){
        color_sat=1.0-(fract(color_sat));
    }
    
    
    
   
   // if(color_hue<0.0){
     //   color_hue=1.0-(abs(color_hue));
    //}
    if(color_sat<0.0){
        color_sat=1.0-(abs(color_sat));
    }
    
    
    
    //this may prove more aesthetically pleasing but
    //will change behavior as well most likely
   // color_hue=color_bright;
    
    //maybe try tying together brightness and hue a little stronger
  //  color_bright=fract(color_hue+color_bright)/2.0;
    
    
  
    //maybe a switch for this too?
    //color_bright=clamp(color_bright,0.0,1.0);
    
    
    
    
    
    
    
    */
    
    
    
    
    
    
    


    
    
    
    
    /*
    //these is just pure vector calcuulations
     //there isn't any dection on x and y just blurring
    color = (color + yw*texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0)))/2.0;
    
    
    
    color =(color+ xw*texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0)))/2.0;

    
    
    if(color==texture2DRect(tex0, texCoordVarying + vec2(0.0, 0.0))){
        color=color*ff;
    }
    
     
     */
    
    
    
    
    
    
    
    
    
    
    
    //this version is for hsb styles stuffs in the detect and displace model
    
    
     
     
     float color_xbright=c_l_hsb.z;
     float color_xhue=c_l_hsb.x;
     float color_xsat=c_l_hsb.y;
     
     
     
     
     
     float color_ybright=c_d_hsb.z;
     float color_yhue=c_d_hsb.x;
     float color_ysat=c_d_hsb.y;
     
     
     
     
    
    if(color_bright<color_ybright){
        
        color_bright = (color_bright+yw*color_ybright)/2.0;
       // color_hue = (color_hue+color_yhue)/2.0;
        color_sat = (color_sat+color_ysat)/2.0;
    
        
       // color_bright = (color_bright+yw*color_flipybright)/2.0;
       // color_hue = (color_hue+color_flipyhue)/2.0;
       // color_sat = (color_sat+color_flipysat)/2.0;
    }
    
    if(color_bright<color_xbright){
        
        
        color_bright =(color_bright+xw*color_xbright)/2.0;
       // color_hue =(color_hue+color_xhue)/2.0;
       color_sat = (color_sat+color_xsat)/2.0;
        
        
       // color_bright =(color_bright+xw*color_flipxbright)/2.0;
       // color_hue =(color_hue+color_flipxhue)/2.0;
       // color_sat = (color_sat+color_flipxsat)/2.0;
    }
    
   
   color_hue = (color_hue+yw*color_yhue)/2.0;
    color_hue =(color_hue+xw*color_xhue)/2.0;

  
    
   // color_hue=(color_hue+hue_vn/4.0+hue_m/4.0)/3.0;
    
   // float current_bright=rw*color.r+gw*color.g+bw*color.b;
    
    
   

    if(color_bright==color_hsb.z){
        color_bright=color_bright*ff;
       // color_hue=color_hue*ff;
    }
    
   // if(color_hue==color_hsb.x){
       // color_bright=color_bright*ff;
      //   color_hue=color_hue*ff;
  //  }
    color_hue=color_hue*2.0*rw;
    color_bright=color_bright*2.0*bw;
    color_sat=color_sat*2.0*gw;
    
    
    color_hue=fract(color_hue);
    
    //if(color_hue>1.0){color_hue=1.0-color_hue;}
    color_hue=abs(color_hue);
    
    
    color_bright=fract(color_bright);
    color_bright=abs(color_bright);
    
    color_sat=fract(color_sat);
    color_sat=abs(color_sat);
    
    
    
    
    
    
     
     
       //here is where i test orders of operation in dealing with overflow values
    //there is probably some difference that occurs if u do each hsb channel seperate
    //and if u do them after conversion no doubt
   
    
    
    
    
    
  

    
    
    //this bits is using the brightness for comparing
    //the brightness was originally calclated using the rgb channels
    //this version is kind of messy and uses entire colors
    //need to figure out more elegant color space worlds!
   /*
    if(color_bright<color_ybright){
    
    color = (color + yw*texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0)))/2.0;
    }
    
    if(color_bright<color_xbright){
    
    
    color =(color+ xw*texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0)))/2.0;
    }
    
    float current_bright=rw*color.r+gw*color.g+bw*color.b;
    
    
    
    if(current_bright==color_bright){
        color=color*ff;
    }
    
    
    */
    
    
    
    
    
    
    
    
    
    
    
    
    
    //this is supposed to be monochrome but there is something logically wrong with this whole thing
    /*
    
    if(color_bright<color_ybright){
        
        color.r = (color.r + yw*texture2DRect(tex0, texCoordVarying + vec2(0.0, blurAmnty * -1.0)).r)/2.0;
    }
    
    if(color_bright<color_xbright){
        
        
        color.r =(color.r+ xw*texture2DRect(tex0, texCoordVarying  + vec2(blurAmntx * 1.0, 0.0)).r)/2.0;
    }
    
    float current_bright=color.r;
    
    
    
    if(current_bright==color_bright){
        color.r=color.r*ff;
    }
    color.g=color.r;
    color.b=color.r;
    
  //  color=(color.r,color.r,color.r,1.0);
    */

   // if(color<1){color=color*-1};
    
// color.r=mod(color.r,1);
//color.g=mod(color.g,1);
//color.b=mod(color.b,1);
    
  //  color.r=abs(color.r);
    //color.g=abs(color.g);
    //color.g=abs(color.g);
    
    
    
    
  
 //   vec4 color2 =vec4(rw*color.r,gw*color.g,bw*color.b,1.0);
  
    // vec3 rgb=vec3(hsv2rgb(vec3(color_hue,color_sat,color_bright)));
    
      vec3 rgb=vec3(hsv2rgb(vec3(color_hue,color_sat,color_bright)));
     vec4 color2=vec4(rgb,1.0);
    
   //   color2=fract(color2);
    //color2=abs(color2);
    
    color2= vec4(mix(color2,color,ll));

   //add a switch for this
  
   
    //this one too
    
    gl_FragColor = (color2);
  //  gl_FragColor = (color.r,color.r,color.r,1.0);
}
