import "./MenuBanner.css";


/**
 * @interface MenuBannerProps
 * @brief Propriedades do componente MenuBanner.
 * @property {string} gameName Nome do jogo.
 * @property {string} gameDescription Descrição do jogo.
 * @property {string} gameImage URL da imagem do jogo.
 * @property {number} id Identificador único do banner.
 * @property {(id: number, gameName: string) => void} action Função chamada ao clicar no botão "JOGAR".
 * @property {string} [className] Classe CSS adicional para personalização.
 */
interface MenuBannerProps{
    gameName:string;
    gameDescription:string;
    gameImage:string;
    id:number
    action:(id:number, gameName:string)=>void;
    className?:string;
}

/**
 * @brief Componente que representa um banner de jogo no menu.
 * @param {MenuBannerProps} props Propriedades do componente.
 * @return {JSX.Element} Retorna o componente do banner do jogo.
 */
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