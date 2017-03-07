


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
        //Change the direction with a random Number that varies depending on the difficulty
        playerDir = (player.transform.position - transform.position).normalized;

    }


}