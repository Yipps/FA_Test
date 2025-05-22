# To Test
- Inventory
  - (I) brings up inventory
  - (esc) exits inventory
  - (M1) Interacts. Can pickup items if inventory isnt full
  - Drag and drop thumbnails of items to either display them in the center view or to swap positions
  - (R) Resets the view on 3D models
  - Drag the thumbnails to Forget Note area to delete item
- Dialogue
  - (M1) Interacts with the dummies and brings up the dialogue interface
  - (M1) Continues to the next dialogue line unless a choice needs to be made. Click the choices to branch dialogue.


Sample playthrough for convienece 
https://drive.google.com/file/d/1Q9GOrU1lSoJuYMRzCT3pwiNmryF8R9a-/view?usp=sharing

# Breakdown
## Inventory System

### Design
I wanted the systems as decoupled and modular as possible to allow designer flexibility. Inventory functionality can be added via an Actor component and any InventoryWidget can display and edit all its contents. Theres two are the core components to handle an inventory concept. The same components can be extended to add inventory functionality to either physical objects like chests or wardrobes or other NPCs.

For the 3D view for models a seperate actor is spawned Photoroom setup is spawned with a camera and various lighting. The photoroom can be extended to create different lighting setups to better highlight certain details for the items

### Technical breakdown
Inventory
- InventoryActorComponent
  - Holds list of DA_items, events and functions to check and manage contents
- InventoryWidget
  - Inspects the InventoryActorComponent displaying visuals. Creates corresponding amount of InventorySlotWidgets
  - Listens to inventory delegates to change visuals
  - Calls functions on the InventoryActorComponent to change contents
- InventorySlotWidget
  - Simple widget that displays thumbnail of a DA_item
- InventoryView
  - Simple widget that displays the photorooom's rendertarget if the DA_Item has a model or just a thumbnail if it doesnt

Photoroom
- Actor that is spawned by the GameMode
- Contains a basic 3 point lighting setup
- Contains logic to move and rotate mesh by its center instead of pivot

PickupActors
 - Interactable actor that holds a item data and tries to add itself to the interactor if it has a Inventory Actor Component and isn't full

### Future considerations
- Photoroom
  - Rendering needs to be more isolated. Other light is effecting the mesh and the room is viewable by the player
- Move logic away from pawn to player controller. Pawn was bloated for quicker iteration 
  - Input mapping contexts and states are in UI/Pawn should move them all in the same places in the controller
  - Liklely will want an entire subsystem dedicated to UI. Currently lot of triggers are in the Pawn 
- Proper selection states for slots and deleting via button
- Additional tooltips hovering item slots
- Proper memory management for assets. All assets are hard references.

## Dialogue System

### Design
A dialogue system can be quite a complex task. For the scope of this I wanted basic one on one dialogue with simple branching dialogue. 

I implemented dialogue as a very simple N-ary tree of dialogue node UObjects thats saved in a Data Asset. For simplicity I used UObjects because they can be created inline in the editor and allowed me to avoid creating additional assets for branching. The basic idea of a node being a line of dialogue offers a lot of control and extendibility. Traversing connected dialogue is easy and you could easily extend the class for more complex logic like having requirements to start a branch of dialogue or events that flag major decisions in the story. However this granulairty will need a better editor 

![image](https://github.com/user-attachments/assets/2cc2fbc6-6d07-436c-8c2d-aa5ce71faf50)

Major limitation of this method is the lack of ability to connect back to a previous dialogue line. I would highly reccomend a custom editor or plugin to manage dialogue data in a graph based way instead of a hierarchy like the image above.
Ideally lines are swapped from UObjects to DataAssets that reference other DataAssets changing the structure from a tree to a graph

### Technical breakdown
Dialogue
- DialogueNode
  - Contains a single text and a array of FChoices
    - FChoice is just a single text representing the player's line and a connection to a different DialogueNode
- DialogueWidget
  - Takes in a single Node and can traverse accordingly
  - Display speaker name and dialogue
  - Displays a subwidget for choices if prompted
 - DialogueSpeakerComponent
   - Contains dialogue asset
   - (TODO) Implement logic to check the state of dialogue. Be responsible for starting the dialogue interaction instead of the owner Actor

### Future Considerations
- Ideally have a graphical interface to construct dialogue
- Animations and events for the dialogue to slowly fill in similar to how Flawless Abbey currently is implemented
- I wanted camera transitions to make the dialogue more engaging
- Account for multiple speakers
- Proper memory management for the data assets. All references are hard references. Will become a biger issue if SFX and additional data is needed.
