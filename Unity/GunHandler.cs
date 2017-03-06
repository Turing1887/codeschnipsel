using VRTK;

public class GunHandler : MonoBehaviour{
    public TriggerHandler triggerHandler;
    public GameObject gunPointer;
    public bool enemyHit;
    Vector3 fwd;
    Vector3 origin;
    RayCastHit hit;

    void Start(){
        origin = gunPointer.transform.position;
        fwd = gunPointer.transform.TransformDirection(Vector3.forward);
    }
    void Update(){
        if(triggerHandler.G_TRIGGER_CLICKED){
            Invoke("Fire",50.0f);
        }
    }

    void Fire(){
        if(Physics.RayCast(origin,fwd,out hit, 30.0f)){
            if(hit.collider.CompareTag("Target")){
                enemyHit = true;
            }
        }
    }

    public bool GunIsInPlace(){
        if(Physics.RayCast(origin,fwd,out hit, 30.0f)){
            if(hit.collider.CompareTag("PlayArea")){
                return true;
            }
            else{
                return false;
            }
        }
    }

}