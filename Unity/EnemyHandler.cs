


public class EnemyHandler : MonoBehaviour{

    public DuelHandler duelHandler;
    public GameObject player;
    public Vector3 playerDir;

    void Update(){
        if(duelHandler.gameStart){
            Shoot();
        }
    }
    void Shoot(){


    }

    void TakeAim(){
        

    }


}