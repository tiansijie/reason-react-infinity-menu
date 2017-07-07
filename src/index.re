type tree = array Tree.node;

let component = ReasonReact.statelessComponent "InfinityMenu";

let make tree::(tree: tree) _children => {
  let convertTreeToDiv node::(node: Tree.node) => {};
  let convertTree tree::(tree: tree) => {
    let results =
      tree |>
      Js.Array.reduce
        (
          fun accu (node: Tree.node) => {
            let id = node##id;
            accu |>
            Array.append [|
              <div key=id> (ReasonReact.stringToElement node##name) </div>
            |]
          }
        )
        [||];
    ReasonReact.arrayToElement results
  };
  {
    ...component,
    render: fun _self => {
      let displayTree = convertTree tree;
      <div> displayTree </div>
    }
  }
};

let jsComponent =
  ReasonReact.wrapReasonForJs
    ::component (fun jsProps => make tree::jsProps##tree [||]);
