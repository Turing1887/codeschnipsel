


public class GunParticle : MonoBehaviour{

    public GameObject particlePrefab;
    public TriggerHandler triggerHandler;
    public GameObject gunPointer;
    ParticleSystem system;

    void Awake(){
        system = particlePrefab.GetComponent<ParticleSystem>();
    }

    void Update(){
        if(triggerHandler.G_TRIGGER_CLICKED){
            DoEmit();
        }
    }

    void DoEmit(){
        Instantiate(particlePrefab,gunPointer.position);
        if(!system.IsAlive()){
            Destroy(particlePrefab);
        }
    }

}