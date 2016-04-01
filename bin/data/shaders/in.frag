varying vec2 texcoord0;
uniform sampler2DRect tex0;
uniform sampler2DRect noise;
uniform vec2 texOffset;


void main(){
    vec4 cur = texture2DRect(tex0, texcoord0);
    vec4 noi = texture2DRect(noise, texcoord0);
    
    gl_FragColor = vec4( cur.x, noi.y, noi.z, 1.0) ;
}