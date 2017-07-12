## reason-react-infinity-menu

A reason-react implimentation of [react-infinity-menu](https://github.com/socialtables/react-infinity-menu)

#### How to run

```
npm start
npm run build
```

#### onNodeMouseClick(event, { tree, node, keyPath })
This function will get call when user click on the folder(node).
The function arguments include ```event```, ```tree```and ```node```.
* ```event``` is the mouse click event.
* ```tree``` is the updated tree, you should update your own tree accordingly.
* ```node``` is the folder(node) the user clicked on. Including the id, name, isOpen and children.
* ```keyPath``` is the path from root to current node

#### onLeafMouseClick(event, { leaf, keyPath })
Bind to the onClick on the leaf.
This function will get call when user click on the item(leaf).
The function arguments include ```event```, ```leaf``` and ```keyPath```.
* ```event``` is the click event.
* ```leaf``` is the item user clicked on. Includes name, id and all data the user inputs when they pass in the tree.
* ```keyPath``` is the path from root to current node


#### onLeafMouseUp(event, { leaf, keyPath })

#### onLeafMouseDown(event, { leaf, keyPath })



*WIP*
