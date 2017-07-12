type tree = array Tree.node;

let component = ReasonReact.statelessComponent "InfinityMenu";

let make
    tree::(tree: tree)
    ::onNodeMouseClick
    ::onLeafMouseClick=?
    ::onLeafMouseUp=?
    ::onLeafMouseDown=?
    _children => {
  let onNodeClick (keyPath: string) (node: Tree.node) event _self => {
    node##isOpen#=(
                    Js.Null_undefined.return (
                      switch (Js.Null_undefined.to_opt node##isOpen) {
                      | Some isOpen => not isOpen
                      | None => true
                      }
                    )
                  );
    onNodeMouseClick event {"node": node, "tree": tree, "keyPath": keyPath}
  };
  let onTreeLeafClick (keyPath: string) (node: Tree.node) event _self =>
    switch onLeafMouseClick {
    | Some click => click event {"leaf": node, "keyPath": keyPath}
    | None => ()
    };
  let onTreeLeafMouseDown (keyPath: string) (node: Tree.node) event _self =>
    switch onLeafMouseDown {
    | Some mousedown => mousedown event {"leaf": node, "keyPath": keyPath}
    | None => ()
    };
  let onTreeLeafMouseUp (keyPath: string) (node: Tree.node) event _sefl =>
    switch onLeafMouseUp {
    | Some mouseup => mouseup event {"leaf": node, "keyPath": keyPath}
    | None => ()
    };
  let rec setDisplayTree (node: Tree.node) (keyPath: string) (level: int) self => {
    let id = node##id;
    let newLevel = level + 1;
    let currNode =
      switch (Js.Null_undefined.to_opt node##children) {
      | Some _children =>
        switch (Js.Null_undefined.to_opt node##customComponent) {
        | Some customComponent => [|
            ReasonReact.createElement
              customComponent
              props::{
                "key": {j|$keyPath+$id|j},
                "index": {j|$keyPath+$id|j},
                "name": node##name,
                "onClick": self.ReasonReact.handle (onNodeClick keyPath node)
              }
              [||]
          |]
        | None => [|
            <li
              className="infinity-menu-node-container"
              key={j|$keyPath+$id|j}
              onClick=(self.ReasonReact.handle (onNodeClick keyPath node))>
              (ReasonReact.stringToElement node##name)
            </li>
          |]
        }
      | None =>
        switch (Js.Null_undefined.to_opt node##customComponent) {
        | Some customComponent => [|
            ReasonReact.createElement
              customComponent
              props::{
                "key": {j|$keyPath+$id|j},
                "index": {j|$keyPath+$id|j},
                "name": node##name,
                "onClick":
                  self.ReasonReact.handle (onTreeLeafClick keyPath node),
                "onMouseDown":
                  self.ReasonReact.handle (onTreeLeafMouseDown keyPath node),
                "onMouseUp":
                  self.ReasonReact.handle (onTreeLeafMouseUp keyPath node)
              }
              [||]
          |]
        | None => [|
            <li
              className="infinity-menu-leaf-container"
              key={j|$keyPath+$id|j}
              onClick=(self.ReasonReact.handle (onTreeLeafClick keyPath node))
              onMouseDown=(
                self.ReasonReact.handle (onTreeLeafMouseDown keyPath node)
              )
              onMouseUp=(
                self.ReasonReact.handle (onTreeLeafMouseUp keyPath node)
              )>
              (ReasonReact.stringToElement node##name)
            </li>
          |]
        }
      };
    switch (Js.Null_undefined.to_opt node##isOpen) {
    | Some isOpen =>
      if isOpen {
        switch (Js.Null_undefined.to_opt node##children) {
        | Some children =>
          children |>
          Js.Array.reducei
            (
              fun prev (child: Tree.node) index =>
                prev |>
                Js.Array.concat (
                  setDisplayTree
                    child {j|$keyPath.children.$index|j} newLevel self
                )
            )
            currNode
        | None => currNode
        }
      } else {
        currNode
      }
    | None => currNode
    }
  };
  {
    ...component,
    render: fun self => {
      let displayTree =
        tree |>
        Js.Array.reducei
          (
            fun accu (node: Tree.node) index =>
              accu |>
              Js.Array.concat (
                setDisplayTree node (string_of_int index) 0 self
              )
          )
          [||];
      <div> (ReasonReact.arrayToElement displayTree) </div>
    }
  }
};

let jsComponent =
  ReasonReact.wrapReasonForJs
    ::component
    (
      fun jsProps =>
        make
          tree::jsProps##tree
          onNodeMouseClick::jsProps##onNodeMouseClick
          onLeafMouseClick::?(
            Js.Null_undefined.to_opt jsProps##onLeafMouseClick
          )
          onLeafMouseUp::?(Js.Null_undefined.to_opt jsProps##onLeafMouseUp)
          onLeafMouseDown::?(Js.Null_undefined.to_opt jsProps##onLeafMouseDown)
          [||]
    );
