

public class DuelHandler : MonoBehaviour{

    public bool victory;
    public bool tied;
    public bool loss;
    public bool gameStart;
    public float countdown;
    public GunHandler gunHandler; 
    public EnemyHandler enemyHandler;

    void Start(){
       countdown = 3000.0f;
    } 

    void FixedUpdate(){
        if(gunHandler.GunIsInPlace){
            countdown -= Time.deltaTime;
            if(countdown == 0){
              Invoke("WinningCondition",100.0f);
            }
        }
    } 

    void WinningCondition(){
        if(gunHandler.enemyHit){
            if(enemyHandler.playerHit){
                tied = true;
            }
            else if(!enemyHandler.playerHit){
                victory = true;
            }
        }
        else if(!gunHandler.enemyHit){
            if(enemyHandler.playerHit){
                loss = true;
            }
            else if(!enemyHandler.playerHit){
                tied = true;
            }
        }
    }

}