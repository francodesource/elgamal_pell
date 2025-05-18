//
// Created by fvfra on 11/04/2025.
//
#include "../include/pq_con.h"

#define BASE 32 // the base of the numbers

typedef struct {
    char* _512 [4];
    char* _1024[4];
    char* _1536[4];
    char* _3840[4];
    char* _7680[4];
} pq_con_t;

const pq_con_t PQ_CON = {
    ._512 = {
        "3rjk4vqdqg7lrj6pp7ajd2srjchgd62avvv6fj9uadi44liec5mnig742lv45pe95ogekekh78ko22gs1bm5cj3idke1gkdvtupejkl",
        "1tpq2ft6t83qtpjcsjl9mhedpm8o6j15fvvj7pkv56p22ap762rbp83i1avi2sn4is87a7a8jkac118e0lr2m9hp6q70oa6vuvcn9qb",
        "2",
        "2sn372loo0a1d3lsed2o3psh4q0j3nsbtiqultl1ct5k9akdel7onel2d20haik2e4u1nrdi0cr6qbe0ghqlaqtbeqarop7lkuf75re"
        },
    ._1024 = {
        "eslj2ekpoulukpqm4p6sgp4vf1vau5jpaao4j52b3ncvr81endr4l2rnr9efke5hb0r7hrnjp9fm89vqhe5916q73g6hu2jvq3uei8klnoj3m0ijri6d3s65e2vlaheer2gqahikko47o9pel8recgkmbjf3gqnbtabanph9jjommmjlgf0e0ahlt6n6mj4eh1i4b0doatr35",
        "7eaph7acsfavactb2cje8cifngvlf2psl5c29ih5hrmftk0nbmtiahdrtkn7q72olgdjotrpsknr44vt8n2kgjd3ho38v19vt1v794aars9hr099tp36hu32n1fql8n7dh8d58paac23s4snakdn68ab5pnhodblul5lbsokppsbbb9qo7g7058qujbjb9i78gp25g6s5ethj",
        "2",
        "5tu1q8n8s9u1p8jd1k623midh0c85rbvvqije157338hvpg1pjhkhm71pq7mrq7rgru1vc6lhaae90elfg58c1ue9c098r3md18s0dmhhrocob7hmg4ngrlhvrdrf41htcln0h9b13num5qr4sbq2hl5ss8kc6a5ng4kddtpkrkdlre9rfv6ba9teanceo2ngi0fjba81bumr"
        },
    ._1536 = {
        "1ogphp906rh99eq98ufbnaeeur9f99i7btjfilkehobgesj6h61i17canm33hqbr011jgqe7krllc0tfgctbm19ju2pv8dh3j6n6nhbclhhuml67mh8ob00aglgem9a0cq7dons8737mhalv1navbm31s2v1u36n38dhkp33irpom1amoa34i7nrqhqg31gatoil6houcrvlp09beh1a5k0l7s7ai9ekgc5mgiq4lq8ueo2uncg358vchfs6qa0eqf119i2sv3db4q8r2v7sd657betv671p4cs80hk168f8vqp1jk71",
        "s8coskg3dokknd4kf7lrl77fdknkkp3lupnpaq78s5o7e9j8j0p0jm5br1hot5tg0gpod73qdqqm0eno6elr0kpv1cvk6ohpjbjbolmaoovbaj3r8kc5g058ao7b4l06d3msbu43hjr8lavgrlflr1gu1fgv1jbhk6oqchhpdssb0lbc51i93rtt8t81go5es9aj8sf6dvqsg4ln8gl2q0aju3l94na862r89d2at4f7c1fbm81ikfm8nu3d507d7ggkp1efhmlid4dhfju6j2jlnevj3gsi6e408q0j47kftcgpq3h",
        "5",
        "q3ale05o6hpai3c0lboarrjav10jff7f3vrd5aeb0sjf39ouk8sc7ntaghml0nn9lh4ov50ufu3nhp0drtv69ehs6rqdrijnskea6i482agv6rcgf7di466cemgo5ogd4bugd2p3eebraagt37t2brn5jk8945tolsku23pgj5e8oog28371qfiitabecr7rarff75eel69tput9he56rdi54raqcisa8lhfvlj2d6hk48a67tolbshjdufp102jvov0pf1j7544lo5u8g324j6fbcq9nr6l8erev01eohvpq4l2cie"
        },
    ._3840 = {
        "q0benldp96kl5arh4hmad1n67s2taqrg2rt74t1t8imoplseb9drrm6iq8eb1pe0mgckpf5t2t7qa2ctq13nadclf9s99tbhbkkflchn0oa21sduohd4g0ppdfkesh2jvo2egupgl6483koo93lq25ugjks5gl97kbu67ri03l8p8l0blr7pdqau68cuk4h0eli6k775s7fcrrb5bvvub8bign76ikqjesiv91jg7i3ea1kgg9odniqsc0hvei71oa84csjq2a50j3fipg98timl62642o2b8efu41r4oukqj8pjesqrlkgsdnvu5bqm82f91f1go6rbkft967lous6b56ckg0jvqblgs7f6hg2ao25rsri2ofd2seotuoda1e1cjc1gshiov1ff5s3tr01vieachsmrrnih40mu85vg21k26hdfu0peu8145ltg60fr0i2jjuhv4btdh1d3p89rcgfgntcdrsdjpsbv8sb3gufuid07jbn7j9ka7tm08f6ob214089k14p42fvjr1vnaapnneu5qif54isodf7ojput0h8ovoca47ffm07n85gbh2a3fforkr8b4c0uf72r61arm8iph9lkolfioquuac7vantbidmvqofm057a97515g389oaqf6ipop0e5svp0s8l4lamk9f6pf9klvlcmvpfheeru10fcte434q7kcq2rt43c3qhk5ni8s9hbmv1dj5l4o4cfial94p1ngr258tv1o4rtl9ks2rk49a5",
        "d05nbqmskjaaildoi8r56grj3u1elddo1dujieguk9bccqu75kmttr39d475gsn0b86acniuhejt516et0hrl6manku4kulolqa7qm8rgc510u6vc8mi80csmnq7e8h9vs178fcoaj241qcc4hqt12v89qe2oakjq5v33tp01qkckag5qtjsmt5f346fa28g7ap3a3jiu3nmdtlilvvv5k5p8bjj9ad9ne9fkgpo3p1n50q884s6rpde608vn93gs5426e9t152g9hnpco4kepbaj1321c15k77v20ticfad9kcpneddqq8e6rvv2ltb417kgngoc3dlq7ukj3qsfe35ij6a809vt5qoe3nj8o15c12tudp1c7mhe7cevc6l0n0m9m0oe8pcfgnniu1utg0vp7568ubdtrp8i0bf42vo10q138mnv0cnf40i2quo307tg919pv8vi5umogmhsk4tm87obum6tu6psu5vke5hof7v96g3plrjpkq53ur047jc5h0i044q0ici17vptgvrl5crrnf2t97ii9ec6njs9sveg8kcfs6523nnr03rk2o5oh51nnsdqdk5i60f7jhdj0ldr49cokqqcanpcdff563vlbulp6rftc7r02jl4jigio1k4s5d7j9cscg72ufsge4aialba4njcnkqavqmbfsnon7dv0g7men21id3q6d1dui1m1t8q2rp4e4olrfgmpiqic267p5akicgrodh2kevgs2duqkqe1dq24l3",
        "2",
        "b0m57b7sqsjml5fn0fm528p09sced0qhi44cu0pt6d710tcmpm9h2tkb49ef4qt0nshsbbag7gagd17j4m9tqonn9hiba948lvt4uqsd647u0ajiuvfochr2p5jqlvdpm50a4unjublrrhu7krniv05f8ueu0tq2s8r7lb1fqk6a0rcns9bs1ditj01kmcjvp0ek6r4muggklu8burb333ba6gh8nlr1mnhbl7hjmm64eeefg5ivqs34qa7qbd7pc5bjr6slqvs5cbdaerh5vqfl1kh384eihpr25acknoo6f8qh1mo1eofs9gg3kacmn3p9cr6ftvcp02uhm2rr4pqcci1d2e562433l5unckg6d7t8af25vammpjp289vgpgf3q36vkrjrqsivtev8jr6pg0phbca8hoch0cslipna3gok66jvimhomst2jkgt05262o7t7vlcmte4bsr54277tbl71o9tgn24vs7cchehdij44hq0kvbv3nj0di0p8di6s97i3u9e94serr0jfp3rv8e7i50uok909d6n1u624v40kejn3oeqmeksegvh6a1jekr1j4f9htea23d25tuci38sf334dgnkpnrfsolvr769s5o7nvo18sctfgeaf9bvk85iecmlevr7s83vs9qubfg3fe568cha90bo6mra6t8sm7danlfsdjtkel42rj4ri7fmk264k2bv9ktdfd9ep1m5vkp8pi5a1qfcn1kiv63sn62frjtdrf1jr96u"
        },
    ._7680 = {
        "g00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e91",
        "80000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000074h",
        "3",
        "e6d3e8o635o8na1g8nsfv6nb018ldd3a24n6t5nnh6hs7gfs4b6uopom1ean36dh8jc6ri4qde37u090e2qhh4s3ht7ht0iqvrva328d02in0375ijjbt98nvs6sol9o785c4o1theav59a0hbone5rknsdfiiveb528of91nkdaictn8nhn8l0re9o97k84bq84n8bk55i5t3fojcik0dgjksafsff8rcpe1jnsildq58c1gj3vm0eg14hbp44le1499b1i3vq6op2nj4gbr2ts0bkkr255126f7tolevdlhjk5jog960hc3c7uh4ebnq4jha9hks1ju8gs47pfm97iq6j7vn43vcntsq5mbsutdlfqqevm3via3umi1d6v1m12fpb57edqclu3bvs9rfrvaq85a9e7gntihc7m13udeihin6kbrcrt7gtqv1gvbboeia9egg4k8bdfp3kqqrmi46fddjqp87bqivmarfa72jsor433eepoqh3iujqu4s3i7ckot3vbsfsjk2g23bv9q8ujqpms96opgcbb4krcdjvchrrbv7u6hu4uerhjqf7qpfhtnns40vfde28ttqtdbrralvdb2imn14pi8f5tauo0ibonhb2gsjkig46hi1kosin35voidt7l6jcc0e04b0el02f3s5m8j23re7vj5bkn3penl8bo7qo55qipn9glrll2mlvv2p6on7d8f745c3dnig3dkj9775bfslueijd1b2figibjmtko896olq43r19k8ce4gsok7bk9ns0g3ir103sc6af501lb6nf7bkjjm6rtreckfecv487qoiure20cs714it05eojbtb6prln003jlpa50aji3g33qon21erpe6inb2fnnh1rcmalirvvh4ps39pn2t6oj8lhlkap23k6fm4v86ce3b311amnfeimnbtdufrr6nrgjomvrdb82j33r50sgjdk0mtqu8jpu2njgeastc798pslnbd8v7qsiecemasoi7df2gu0cnqgrlitnldb5ea0or9uom2icr7nhnp1nk4v39s7jmr2um3tmbbk6teelj42qj60igmaplror0eehmnp0h1q3nato29qq1ibue1fa89dqsfuted9q8dhh0av1omf523ea66o6rimglgsbjlmhgmsgc02eg0rt4r7rvm4gc0l2rfq36fghjkrhm1ho64vbo0avgk29iaq9g16sflph82rd4bdqn1d0c4kpeheijcuqbvbpbbpp4f1vlt858jhp8bqcsec06tavasf5s6s8eab7466s0ijka96jn7hgph4lkgm6q9bp2e7132aie36mj01jbdjtv9nj8s1dt9ho8aog2gqfo4ke5v6aaniuphr9ogvc4oltn8g83ohs9au5n0dj55m8hnl62toi6hcubd265g33emgsj8o6t812rgf1qulqmk7utq1ivqdg6teg8b5hpnu3knb3a5jndp6nv2guhioh9hedgi73on57p7i7o1g7ku7rit4a4umjpo2c"
        }
};

bool primes_q_p_by_size(mpz_t q, mpz_t p, const mp_bitcnt_t size) {
    switch (size) {
        case 512:
            mpz_set_str(q, PQ_CON._512[0], BASE);
            mpz_set_str(p, PQ_CON._512[1], BASE);
            break;
        case 1024:
            mpz_set_str(q, PQ_CON._1024[0], BASE);
            mpz_set_str(p, PQ_CON._1024[1], BASE);
            break;
        case 1536:
            mpz_set_str(q, PQ_CON._1536[0], BASE);
            mpz_set_str(p, PQ_CON._1536[1], BASE);
            break;
        case 3840:
            mpz_set_str(q, PQ_CON._3840[0], BASE);
            mpz_set_str(p, PQ_CON._3840[1], BASE);
            break;
        case 7680:
            mpz_set_str(q, PQ_CON._7680[0], BASE);
            mpz_set_str(p, PQ_CON._7680[1], BASE);
            break;
        default:
            return false;
    }
    return true;
}

bool primes_q_p_d_g_by_size(mpz_t q, mpz_t p, mpz_t d, mpz_t g, const mp_bitcnt_t size) {
    switch (size) {
        case 512:
            mpz_set_str(q, PQ_CON._512[0], BASE);
            mpz_set_str(p, PQ_CON._512[1], BASE);
            mpz_set_str(d, PQ_CON._512[2], BASE);
            mpz_set_str(g, PQ_CON._512[3], BASE);
        break;
        case 1024:
            mpz_set_str(q, PQ_CON._1024[0], BASE);
            mpz_set_str(p, PQ_CON._1024[1], BASE);
            mpz_set_str(d, PQ_CON._1024[2], BASE);
            mpz_set_str(g, PQ_CON._1024[3], BASE);
        break;
        case 1536:
            mpz_set_str(q, PQ_CON._1536[0], BASE);
            mpz_set_str(p, PQ_CON._1536[1], BASE);
            mpz_set_str(d, PQ_CON._1536[2], BASE);
            mpz_set_str(g, PQ_CON._1536[3], BASE);
        break;
        case 3840:
            mpz_set_str(q, PQ_CON._3840[0], BASE);
            mpz_set_str(p, PQ_CON._3840[1], BASE);
            mpz_set_str(d, PQ_CON._3840[2], BASE);
            mpz_set_str(g, PQ_CON._3840[3], BASE);
        break;
        case 7680:
            mpz_set_str(q, PQ_CON._7680[0], BASE);
            mpz_set_str(p, PQ_CON._7680[1], BASE);
            mpz_set_str(d, PQ_CON._7680[2], BASE);
            mpz_set_str(g, PQ_CON._7680[3], BASE);
        break;
        default:
            return false;
    }
    return true;
}