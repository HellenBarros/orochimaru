#include <allegro.h>
#include <math.h>
#include <time.h>

/// variaveis globais
int colidir(int ax, int ay, int bx, int by, int aw, int ah, int bw, int bh);
int m;
int caindo = 1;
float vel_y = 0;
float gravidade = 0.1;
float eixo_y = 0.0;

volatile int timer;
void incrementa_timer() { timer++; }
END_OF_FUNCTION(incrementa_timer)

volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

volatile int milisegundos;
void msec_counter() { milisegundos++; }
END_OF_FUNCTION(msec_counter)

///função menu
int menu()
{
    BITMAP* buf = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* seta = load_bitmap("seta.bmp", NULL);
    BITMAP* fundo = load_bitmap("fundo.bmp", NULL);
    BITMAP* logo = load_bitmap("logo.bmp", NULL);

    int setay = 260;
    m = 1;



    while(m==1)
    {


            if(key[KEY_S])
            {
                setay = 330;
            }



            if(key[KEY_W])
            {
                setay = 260;
            }
            if(setay == 260 && key[KEY_ENTER])
                {
                    m = 0;
                    END_OF_FUNCTION(menu);

                }
            if(setay == 330 && key[KEY_ENTER])
                {


                   m = 2;
                }




    draw_sprite(buf, fundo, 0, 0);
    draw_sprite(buf, logo, 270, 40);
    textout_ex(buf, font, "Start Game", 310, 268, makecol(255,255,255), -1);
    textout_ex(buf, font, "Exit", 310, 338, makecol(255,255,255), -1);
    draw_sprite(buf, seta, 230, setay);
    draw_sprite(screen, buf, 0, 0);

    }
    destroy_bitmap(buf);
    destroy_bitmap(fundo);
    destroy_bitmap(seta);

    return m;
}



int main()
{
///iniciando
  allegro_init();
  install_timer();
  install_keyboard();
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
  set_window_title("Naruto");

  exit_program = FALSE;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  timer = 0;
  LOCK_FUNCTION(incrementa_timer);
  LOCK_VARIABLE(timer);
  install_int_ex(incrementa_timer, SECS_TO_TIMER(1));


  milisegundos = 0;
  LOCK_FUNCTION(msec_counter);
  LOCK_VARIABLE(milisegundos);
  install_int_ex(msec_counter, MSEC_TO_TIMER(1));

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

  BITMAP* naruto[11];
  naruto[0] = load_bitmap("andou1.bmp", NULL);
  naruto[1] = load_bitmap("andou2.bmp", NULL);
  naruto[2] = load_bitmap("andou3.bmp", NULL);
  naruto[3] = load_bitmap("andou4.bmp", NULL);
  naruto[4] = load_bitmap("andou5.bmp", NULL);
  naruto[5] = load_bitmap("andou6.bmp", NULL);
  naruto[6] = load_bitmap("andou7.bmp", NULL);
  naruto[7] = load_bitmap("andou8.bmp", NULL);
  naruto[8] = load_bitmap("parado.bmp", NULL);
  naruto[9] = load_bitmap("pulando.bmp", NULL);
  naruto[10] = load_bitmap("murro_4.bmp", NULL);

  BITMAP* orochimaruataque[18]; //ataque do orochimaru
  orochimaruataque[0] = load_bitmap("final1.bmp", NULL);
  orochimaruataque[1] = load_bitmap("final2.bmp", NULL);
  orochimaruataque[2] = load_bitmap("final3.bmp", NULL);
  orochimaruataque[3] = load_bitmap("final4.bmp", NULL);
  orochimaruataque[4] = load_bitmap("final5.bmp", NULL);
  orochimaruataque[5] = load_bitmap("final6.bmp", NULL);
  orochimaruataque[6] = load_bitmap("final7.bmp", NULL);
  orochimaruataque[7] = load_bitmap("final8.bmp", NULL);
  orochimaruataque[8] = load_bitmap("final9.bmp", NULL);
  orochimaruataque[9] = load_bitmap("final10.bmp", NULL);
  orochimaruataque[10] = load_bitmap("final11.bmp", NULL);
  orochimaruataque[11] = load_bitmap("final12.bmp", NULL);
  orochimaruataque[12] = load_bitmap("final13.bmp", NULL);
  orochimaruataque[13] = load_bitmap("final14.bmp", NULL);
  orochimaruataque[14] = load_bitmap("stop.bmp", NULL);
  orochimaruataque[15] = load_bitmap("stop2.bmp", NULL);
  orochimaruataque[16] = load_bitmap("stop3.bmp", NULL);
  orochimaruataque[17] = load_bitmap("stop4.bmp", NULL);



  BITMAP* cenario_h = load_bitmap("cenario_h.bmp", NULL);
  BITMAP* cenariop[8];
  for(int i =0; i<8;i++){cenariop[i] = load_bitmap("cenariop.bmp", NULL);}



  BITMAP* vida[11];
  vida[10] = load_bitmap("vida_cheia.bmp", NULL);
  vida[9] = load_bitmap("vida_9.bmp", NULL);
  vida[8] = load_bitmap("vida_8.bmp", NULL);
  vida[7] = load_bitmap("vida_7.bmp", NULL);
  vida[6] = load_bitmap("vida_6.bmp", NULL);
  vida[5] = load_bitmap("vida_5.bmp", NULL);
  vida[4] = load_bitmap("vida_4.bmp", NULL);
  vida[3] = load_bitmap("vida_3.bmp", NULL);
  vida[2] = load_bitmap("vida_2.bmp", NULL);
  vida[1] = load_bitmap("vida_1.bmp", NULL);
  vida[0] = load_bitmap("vida_vazia.bmp", NULL);

  ///Variaveis
  float eixo_x = 0.0;
  float eixo_x_personagem = 250.0;
  float vel_x = 1.0;
  int num_frames = 8;
  int frame_atual = 0;
  int tempo_troca = 90;
  double direcao;
  int num_orochimaruataque = 18;
  int frame_orochimaruataque = 0;

  int num_queda=5;
  int frame_queda = 0;
  int frame_vida = 10;
  int orochi = 0;



   int marcador = timer; // MARCADOR DE TEMPO

    menu();
    if(m==2)
    {
        fecha_programa();
    }

  ///GAME LOOP
  while(!exit_program)
  {
     //CONTROLES

          if(key[KEY_ESC])
          {
              menu();
              if(m==2)
              {
                  fecha_programa();
              }
          }

         if(key[KEY_A])
         {
            frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
            direcao = DRAW_SPRITE_H_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)


            eixo_x_personagem = eixo_x_personagem - vel_x; //naruto que anda
         }
         else if(key[KEY_D])
         {
             frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
             direcao = DRAW_SPRITE_NO_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)

            eixo_x_personagem = eixo_x_personagem + vel_x; //naruto que anda
         }

         else
         {
             frame_atual = 8; // FRAME DO NARUTO PARADO


         }

          if(key[KEY_SPACE])
         {
             frame_atual = 10;
         }

         if(key[KEY_W]&& eixo_y > 80) // PULO
         {


                vel_y = -3;
                frame_atual = 9;
                vel_y += gravidade; eixo_y += vel_y;

         }


        else{vel_y += gravidade; eixo_y += vel_y;} // FUNÇÃO DE GRAVIDADE

    if(orochi != 18){frame_orochimaruataque = (milisegundos / 150) % num_orochimaruataque;
        if(eixo_x_personagem + 100 > eixo_x+500 && eixo_x_personagem < eixo_x_personagem+100)


        {
            if(eixo_x<=-709 && eixo_x>=-730){eixo_x = -709;} // BLOQUEIA A PASSAGEM PELA FRENTE DA COBRA
            else if(eixo_x>=-860 && eixo_x<=-740){eixo_x = -860;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA
            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_orochimaruataque =18;

                orochi= 18;

            }
            else if(timer - marcador >=2){frame_vida= frame_vida - 2; marcador = timer;} // SERVE PARA NÃO FICAR PERDENDO VIDA CONTINUAMENTE
        }

    }


         //CONDIÇÕES


         if(eixo_x<-600)
         {
             eixo_x = -600; // PONTO FINAL DO EIXO X
         }
         if(eixo_x>0)
         {
             eixo_x = 0; // PONTO INICIAL DO EIXO X
         }


         if(eixo_y > 460.0)
         {
             eixo_y = 460.0; // PONTO FINAL EIXO Y
         }






         //DRAW


         draw_sprite(buffer, cenario_h, 0, 0);
         draw_sprite(buffer, cenariop[0], eixo_x, 10);
         draw_sprite_ex(buffer, orochimaruataque[frame_orochimaruataque], eixo_x+370, 430, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP); //orochiimaru
         draw_sprite_ex(buffer, naruto[frame_atual], eixo_x_personagem, eixo_y, DRAW_SPRITE_NORMAL, direcao);//PERSONAGEM Naruto
         draw_sprite(buffer, vida[frame_vida], 30, 50);
         textout_ex(buffer, font, "Vida", 40, 40, makecol(255,255,255), -1);
         draw_sprite(screen, buffer, 0, 0);





  }

  ///FINALIZAÇÃOs
  destroy_bitmap(buffer);
  destroy_bitmap(naruto);
  //destroy_bitmap(queda);
  destroy_bitmap(cenario_h);
  destroy_bitmap(cenariop);
  destroy_bitmap(orochimaruataque);


  return 0;
}
END_OF_MAIN();

///FUNÇÃO COLISÃO
 int colidir(int ax, int ay, int bx, int by, int aw, int ah, int bw, int bh){
 if(ax+aw>bx && ax<bx+bw && ay+ah >by && ay<by+bh)return 1; // AX = EIXO X DO PERSONAGEM; AY = EIXO Y DO PERSONAGEM; BX = EIXO X DO OBJETO; BY = EIXO Y DO OBJETO; AW = LARGURA DO PERSONAGEM; AH = ALTURA DO PERSONAGEM; BW = LARGURA DO OBJETO; BH = ALTURA DO OBJETO

    return 0;
    }








