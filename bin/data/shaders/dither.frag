//setup for 2 texture
varying vec2 texcoord0;

uniform sampler2DRect tex0;
uniform vec2 texOffset;// = vec2(1.0,1.0);

uniform float px;
uniform float py;

float err(float i , float j){
    vec4 temp = texture2DRect(tex0, texcoord0+ vec2(i*texOffset.x, j*texOffset.y));
    return temp.y*(1.0 - temp.z) - temp.y * temp.z;
}

void main(){
    
    
    vec4 cur = texture2DRect(tex0,texcoord0);
    
    float sum = cur.x + (2.0*err(-1.5,0.0) + 2.0*err(1.5,0.0) + 2.0*err(0.0,-1.5) + 2.0*err(0.0,1.5) + err(-1.0,-1.0) + err(1.0,-1.0) + err(-1.0,1.0) + err(1.0,1.0))/12.0;
    
    float fx = floor(gl_FragCoord.x);
    float fy = floor(gl_FragCoord.y);
    
    vec4 new = sum > 0.5 ? vec4(cur.x, 1.0-sum, 1.0,1.0) : vec4(cur.x, sum-0.0, 0.0,1.0);
    
    
    
    gl_FragColor = floor(mod(fx,3.0)) == px && floor(mod(fy,3.0)) == py ? new : vec4(vec3(cur), 1.0);
}