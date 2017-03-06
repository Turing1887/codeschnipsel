
using VRTK;


//Script detects if Trigger has been pressed. 
public class TriggerHandler : MonoBehaviour{

    //Global Boolean to determine if trigger has been Clicked
    public bool G_TRIGGER_CLICKED;

    void Start(){
        GetComponent<VRTK_ControllerEvents>.TriggerClicked += new ControllerInteractionEventHandler(GUN_EVENT);
    }
    void GUN_EVENT(object sender, ControllerInteractionEventArgs e){
        G_TRIGGER_PRESSED = true;
    }

}