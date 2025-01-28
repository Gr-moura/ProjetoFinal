import "./MenuBanner.css";

interface MenuBannerProps{
    gameName:string;
    gameDescription:string;
    gameImage:string;
    id:number
    action:(id:number, gameName:string)=>void;
    className?:string;
}

export const MenuBanner = ({gameName, gameDescription, gameImage, id, action, className}:MenuBannerProps) => {
    return (
        <div className={"menubannerbody "+className}>
            <div className="banner">
                <h2 className="gamename">{gameName}</h2>
                <div className="imagetextborder"></div>
                <img className="gameimage" src={gameImage}></img>
                <a className="gamedescription">{gameDescription}</a>
            </div>
            <button className="playbutton" onClick={()=>action(id, gameName)}>
                <h2 className="buttontext">{"JOGAR"}</h2>
            </button>
        </div>
    )
}