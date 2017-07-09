type tree = array Tree.node;

let component = ReasonReact.statelessComponent "InfinityMenu";

let make tree::(tree: tree) ::onNodeMouseClick _children => {
  let onNodeClick (_keyPath: string) (node: Tree.node) event _self => {
    node##isOpen#=(
                    Js.Null_undefined.return (
                      switch (Js.Null_undefined.to_opt node##isOpen) {
                      | Some isOpen => not isOpen
                      | None => true
                      }
                    )
                  );
    onNodeMouseClick event tree
  };
  let rec convertTreeToDiv
          (node: Tree.node)
          (keyPath: string)
          (level: int)
          self => {
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
            onClick=(self.ReasonReact.handle (onNodeClick keyPath node))>
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
                  convertTreeToDiv
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
  let convertTree (tree: tree) self => {
    let results =
      tree |>
      Js.Array.reducei
        (
          fun accu (node: Tree.node) index =>
            accu |>
            Js.Array.concat (
              convertTreeToDiv node (string_of_int index) 0 self
            )
        )
        [||];
    ReasonReact.arrayToElement results
  };
  {
    ...component,
    render: fun self => {
      let displayTree = convertTree tree self;
      <div> displayTree </div>
    }
  }
};

let jsComponent =
  ReasonReact.wrapReasonForJs
    ::component
    (
      fun jsProps =>
        make
          tree::jsProps##tree onNodeMouseClick::jsProps##onNodeMouseClick [||]
    );
