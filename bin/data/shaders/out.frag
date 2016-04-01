//setup for 2 texture
varying vec2 texcoord0;

uniform sampler2DRect tex0;
uniform vec2 texOffset;


void main(){
    vec4 cur = texture2DRect(tex0,texcoord0);
    
    gl_FragColor = vec4( vec3(cur.z), 1.0) ;
}