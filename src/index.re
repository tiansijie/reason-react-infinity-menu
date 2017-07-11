type tree = array Tree.node;

let component = ReasonReact.statelessComponent "InfinityMenu";

let make tree::(tree: tree) ::onNodeMouseClick ::onLeafMouseClick=? _children => {
  let onNodeClick (keyPath: string) (node: Tree.node) event _self => {
    node##isOpen#=(
                    Js.Null_undefined.return (
                      switch (Js.Null_undefined.to_opt node##isOpen) {
                      | Some isOpen => not isOpen
                      | None => true
                      }
                    )
                  );
    onNodeMouseClick event tree node keyPath
  };
  let onLeafClick (keyPath: string) (node: Tree.node) event _self =>
    switch onLeafMouseClick {
    | Some click => click event node keyPath
    | None => ()
    };
  let rec setDisplayTree (node: Tree.node) (keyPath: string) (level: int) self => {
    let id = node##id;
    let newLevel = level + 1;
    let currNode =
      switch (Js.Null_undefined.to_opt node##children) {
      | Some _children => [|
          <li
            className="infinity-menu-node-container"
            key={j|$keyPath+$id|j}
            onClick=(self.ReasonReact.handle (onNodeClick keyPath node))>
            (ReasonReact.stringToElement node##name)
          </li>
        |]
      | None => [|
          <li
            className="infinity-menu-leaf-container"
            key={j|$keyPath+$id|j}
            onClick=(self.ReasonReact.handle (onLeafClick keyPath node))>
            (ReasonReact.stringToElement node##name)
          </li>
        |]
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
          [||]
    );
